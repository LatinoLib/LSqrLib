/*==========================================================================;
 *
 *  File:          LSqrDotNet.cs
 *  Version:       1.0
 *  Desc:		   LSQR.NET test
 *  Author:        Miha Grcar 
 *  Created on:    Oct-2007
 *  Last modified: Oct-2007
 *  License:       Common Public License (CPL)
 *  Note:
 *      See ReadMe.txt for additional info and acknowledgements.
 * 
 ***************************************************************************/

using System;
using LSqrDotNet;

namespace LSqrDotNetTest
{
    class Program
    {
        static void Main(string[] args)
        {
            // In this example we look for argmin{||Ax - b||^2} where A = (  3 -1 ) and b = ( 2 6 )^T.
            //                                                            ( -1 -1 )
            // The exact solution is x0 = -1, x1 = -5.
            LSqrSparseMatrix A = LSqrSparseMatrix.FromDenseMatrix(new double[,] { { 3, -1 }, { -1, -1 } });
            LSqrSparseMatrix A_transp = LSqrSparseMatrix.TransposeFromDenseMatrix(new double[,] { { 3, -1 }, { -1, -1 } });
            double[] b = new double[] { 2, 6 };
            int A_rows = 2;
            int A_cols = 2;
            // perform the computation
            double[] sol = LSqrDll.DoLSqr(A_cols, A, A_transp, b, A_rows + A_cols + 50);
            // output the solution
            for (int i = 0; i < sol.Length; i++)
            {
                Console.WriteLine(string.Format("x{0} = {1}", i, sol[i]));
            }
            // cleanup
            A.Dispose();
            A_transp.Dispose();
        }
    }
}
