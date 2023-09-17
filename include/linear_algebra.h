#ifndef __LINEAR_ALGEBRA_H_
#define __LINEAR_ALGEBRA_H_

#include <cassert>
#include "common.h"



template<typename T>
T dot(matrix<const T> x0,matrix<const T> x1){
  SCOPED_TRACE(dot);
  assert(x0.size() == x1.size());
  const T* x0d=x0.data_handle();
  const T* x1d=x1.data_handle();
  T out(0.0);
  for(size_t i=0;i<x0.size();i++){
    out=out+x0d[i]*std::conj(x1d[i]);
  }
  INCREMENT_MEMORY_READS(2*x0.size()*sizeof(T));  
  INCREMENT_FLOPS(x0.size()*2);
  return out;
}

template<typename T>
void scale_add(const T& alpha,matrix<const T> x,const T& beta,matrix<T> y){
  SCOPED_TRACE(scale_add);
  assert(x.size() == y.size());
  const T* xd=x.data_handle();
  T* yd=y.data_handle();
  for(size_t i=0;i<x.size();i++){
    yd[i]=alpha*xd[i]+beta*yd[i];
  }
  INCREMENT_MEMORY_READS(x.size()*sizeof(T));
  INCREMENT_MEMORY_READS(y.size()*sizeof(T));
  INCREMENT_MEMORY_WRITES(y.size()*sizeof(T));
  INCREMENT_FLOPS(x.size()*3);
}


#endif
