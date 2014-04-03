#ifndef __W_TYPES_H__
#define __W_TYPES_H__
#include <stdio.h>

// integer quantities are either signed or unsigned, and may have
// 8, 16, 32, or 64 bits.  Define the ones you need here.

typedef signed char        int8;
typedef unsigned char      uint8;

typedef short              int16;
typedef unsigned short     uint16;

typedef int                int32;
typedef unsigned int       uint32;

typedef long long          long64;
typedef unsigned long long ulong64;
#ifndef __64BIT__
typedef long64             int64;
#endif
typedef ulong64            uint64;


/*------------------*/
/* Vector type definitions */
/*------------------*/

typedef struct LONG_VECTOR {
  long     length;
  long     *elements;
} lvec;

typedef struct DOUBLE_VECTOR {
  long     length;
  double   *elements;
} dvec;

typedef struct LSQR_INPUTS {
  long     num_rows;
  long     num_cols;
  double   damp_val;
  double   rel_mat_err;
  double   rel_rhs_err;
  double   cond_lim;
  long     max_iter;
  FILE     *lsqr_fp_out;
  dvec     *rhs_vec;
  dvec     *sol_vec;
} lsqr_input;

typedef struct LSQR_OUTPUTS {
  long     term_flag;
  long     num_iters;
  double   frob_mat_norm;
  double   mat_cond_num;
  double   resid_norm;
  double   mat_resid_norm;
  double   sol_norm;
  dvec     *sol_vec;
  dvec     *std_err_vec;
} lsqr_output;

typedef struct LSQR_WORK {
  dvec     *bidiag_wrk_vec;
  dvec     *srch_dir_vec;
} lsqr_work;

#endif
