/*==========================================================================;
 *
 *  File:          LSqrDll.cpp
 *  Version:       1.2
 *  Desc:		   LSQR DLL implementation
 *  Author:        Miha Grcar 
 *  Created on:    Oct-2007
 *  Last modified: Jun-2010
 *  License:       Common Public License (CPL)
 *  Note:
 *      See ReadMe.txt for additional info and acknowledgements.
 * 
 ***************************************************************************/

#include <assert.h>
#include <vector>
#include <map>
#include "LSqr.hpp"
#include "LSqrDll.h"
#include "Synchronize.h"

using namespace std;

#define LOCK(cs) CriticalSectionLock JOIN(lock_, __LINE__)(&cs)
#define DO_JOIN(a, b) a##b
#define JOIN(a, b) DO_JOIN(a, b)

class SparseMatrix;

map<int, SparseMatrix *> matrices;
int matrix_id = -1;

CriticalSection lock_matrices;

class SparseVector
{
private:
    vector<pair<int, double> > m_values;
public:
    int Count()
    {
        return (int)m_values.size();
    }
    pair<int, double> *GetItem(int idx)
    {
        return &m_values[idx];
    }
    void InsertValue(int idx, double val)
    {
        m_values.push_back(pair<int, double>(idx, val));
    }
};

class SparseMatrix
{
private:
    vector<SparseVector> m_rows;
public:
	SparseMatrix(int row_count)
	{
		for (int i = 0; i < row_count; i++) 
		{ 
			m_rows.push_back(SparseVector()); 
		}
	}
    int RowCount()
    {
        return (int)m_rows.size();
    }
    SparseVector *GetRow(int idx)
    {
        return &m_rows[idx];
    }
};

class SparseModel : public Model
{
private:
    SparseMatrix *m_mat;
    SparseMatrix *m_mat_transp;
public:
    SparseModel(SparseMatrix *mat, SparseMatrix *mat_transp) : Model(mat->RowCount(), mat_transp->RowCount()), m_mat(mat), m_mat_transp(mat_transp)
    {
    }
    void matVecMult(long mode, dvec *x, dvec *y)
    {
        if (mode == 0)
        {
            for (int row_idx = 0; row_idx < m_mat->RowCount(); row_idx++)
            {
                SparseVector *row = m_mat->GetRow(row_idx);
                double sum = 0;
                for (int col_idx = 0; col_idx < row->Count(); col_idx++)
                {
                    int vec_idx = row->GetItem(col_idx)->first;
                    double mat_val = row->GetItem(col_idx)->second;
                    double vec_val = x->elements[vec_idx];
                    sum += mat_val * vec_val;
                }
                y->elements[row_idx] += sum;
            }
        }
        else 
        {
            for (int row_idx = 0; row_idx < m_mat_transp->RowCount(); row_idx++)
            {
                SparseVector *row = m_mat_transp->GetRow(row_idx);
                double sum = 0;
                for (int col_idx = 0; col_idx < row->Count(); col_idx++)
                {
                    int vec_idx = row->GetItem(col_idx)->first;
                    double mat_val = row->GetItem(col_idx)->second;
                    double vec_val = y->elements[vec_idx];
                    sum += mat_val * vec_val;
                }
                x->elements[row_idx] += sum;
            }
        }
    }
};

LSQR_API int NewMatrix(int row_count)
{
    LOCK(lock_matrices);
    matrix_id++;
    matrices.insert(pair<int, SparseMatrix *>(matrix_id, new SparseMatrix(row_count)));
    return matrix_id;
}

LSQR_API void DeleteMatrix(int id)
{
    LOCK(lock_matrices);
	delete matrices[id];
    matrices.erase(id);
}

SparseMatrix *GetMatrix(int id)
{
    LOCK(lock_matrices);
    return matrices[id];
}

LSQR_API void InsertValue(int mat_id, int row_idx, int col_idx, double val)
{
    SparseMatrix *mat = GetMatrix(mat_id);
    mat->GetRow(row_idx)->InsertValue(col_idx, val);
}

LSQR_API double *DoLSqr(int mat_id, int mat_transp_id, double *init_sol, double *rhs, int max_iter)
{
    SparseMatrix *mat = GetMatrix(mat_id);
    SparseMatrix *mat_transp = GetMatrix(mat_transp_id);
    int num_rows = mat->RowCount();
    int num_cols = mat_transp->RowCount();
    // init
    Model *model = new SparseModel(mat, mat_transp);	
    Lsqr *lsqr = new Lsqr(model);
    lsqr->allocLsqrMem();
    lsqr->input->lsqr_fp_out = stdout;
    // copy right-hand side vector 
    for (int idx = 0; idx < num_rows; idx++)
    {
        lsqr->input->rhs_vec->elements[idx] = rhs[idx];
    }
    // initial guess for x 
    if (init_sol == NULL)
	{
		for (int col_idx = 0; col_idx < num_cols; col_idx++)
		{
			lsqr->input->sol_vec->elements[col_idx] = 0.0;
		}
	}
	else	
	{
		for (int col_idx = 0; col_idx < num_cols; col_idx++)
		{
			lsqr->input->sol_vec->elements[col_idx] = init_sol[col_idx];
		}
	}
    // input parameters
    lsqr->input->num_rows = num_rows;
    lsqr->input->num_cols = num_cols;
    lsqr->input->damp_val = 0;
    lsqr->input->rel_mat_err = 1.0e-10;
    lsqr->input->rel_rhs_err = 1.0e-10;
    lsqr->input->cond_lim = 0;		
    lsqr->input->max_iter = max_iter;
    // do the main thing
    lsqr->do_lsqr(model);
    // get results
    double *sol = (double *)GlobalAlloc(GMEM_FIXED, num_cols * sizeof(double));
    for (int i = 0; i < num_cols; i++)
    {
        sol[i] = lsqr->output->sol_vec->elements[i];
    }
    // cleanup
    lsqr->freeLsqrMem();
    delete lsqr;
    delete model;
    // all done
    return sol;
}