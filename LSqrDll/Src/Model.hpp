/*
* Model.hpp
* Defines the Model class for use by Lsqr
*
* 16 May 2003: First C++ version by J.A. Tomlin
*/

#ifndef _MATRIX_
#define _MATRIX_

#include "LsqrTypes.hpp"
#include "test_lsqr.hpp"

#include <stdio.h>
#include <stdlib.h> 
/**
 * This class implements a (sparse) matrix for pdco
 */
class Model {

public:

  uint32 nrow;
  uint32 ncol;
  uint32 numElts;
  int32 *rowIndex;
  uint32 *colStarts;
  double  *values;
  double  *rowUpper;
  double  *rowLower;
  double  *colUpper;
  double  *colLower;
  double  *rhs;
  prod_data *prod;
  
  Model(uint32 rowSiz, uint32 colSiz){
    nrow = rowSiz;
    ncol = colSiz;
    prod = new PROD_DATA;
  } 

  ~Model(){
  }

uint32 rowSize(){
    return nrow;
  }  
  
uint32 colSize(){
    return ncol;
  }  

virtual void matVecMult( long, dvec *, dvec *);
  
};
#endif
