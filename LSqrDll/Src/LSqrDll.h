/*==========================================================================;
 *
 *  File:          LSqrDll.h
 *  Version:       1.2
 *  Desc:		   LSQR DLL header
 *  Author:        Miha Grcar 
 *  Created on:    Oct-2007
 *  Last modified: Jun-2010
 *  License:       Common Public License (CPL)
 *  Note:
 *      See ReadMe.txt for additional info and acknowledgements.
 * 
 ***************************************************************************/

#ifndef LSQR_DLL
#define LSQR_DLL

#ifdef LSQRDLL_EXPORTS
#define LSQR_API extern "C" __declspec(dllexport)
#else
#define LSQR_API extern "C" __declspec(dllimport)
#endif

LSQR_API int NewMatrix(int row_count);
LSQR_API void DeleteMatrix(int id);
LSQR_API void InsertValue(int mat_id, int row_idx, int col_idx, double val);
LSQR_API double *DoLSqr(int mat_id, int mat_transp_id, double *init_sol, double *rhs, int max_iter);

#endif