#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "matrix.h"

Matrix sigma2z(const Matrix& s);
Matrix sigma(const Matrix& x);
Matrix dSigma(const Matrix& x);
double cost(const Matrix& x,const Matrix& aims);
Matrix probability(const Matrix& x);
Matrix partialC2x(const Matrix& x, const Matrix& aims);
void backPropagation(Matrix& c2w,Matrix& c2x, Matrix& c2b, //对三个量的偏导数
                     const Matrix& c2xl,const Matrix& w,const Matrix& x,const Matrix& b);
Matrix toNext(const Matrix& w, const Matrix& x,const Matrix& b);


#endif
