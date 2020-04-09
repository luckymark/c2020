#include <cmath>
#include <cassert>
#include "backPropagation.h"

//输入列向量，返回函数值
Matrix sigma(const Matrix& x){
    assert(x.col == 1);
    Matrix m(x.row,x.col);
    for (int i = 0; i < x.row; ++i) {
        m.value[i][0] = 1/(1+exp(-x.value[i][0]));
    }
    return m;
}
//输入列向量，返回σ的导数值
Matrix dSigma(const Matrix& x){
    assert(x.col == 1);
    Matrix m(x.row,x.col);
    for (int i = 0; i < x.row; ++i) {
        double e = exp(-x.value[i][0]);
        m.value[i][0] = e / (1+e)*(1+e);
    }
    return m;
}
//输入最后一层列向量，返回代价
double cost(const Matrix& x,const Matrix& aims){
    assert(x.col == 1 && aims.col == 1);
    Matrix m(x.row,x.col);
    double C = 0;
    for (int i = 0; i < x.row; ++i) {
        C += (x.value[i][0] - aims.value[i][0]) * (x.value[i][0] - aims.value[i][0]) /20;   //TODO
    }
    return C;
}
//最后一层，返回概率
Matrix probability(const Matrix& x){
    assert(x.col == 1);
    Matrix m(x.row,x.col);
    double sum = 0;
    for (int i = 0; i < x.row; ++i) {
        sum += x.value[i][0] * x.value[i][0];
    }
    for (int i = 0; i < x.row; ++i) {
        m.value[i][0] = x.value[i][0] / sqrt(sum);
    }
    return m;
}
//输入最后一层的列向量，返回C关于xL的偏导函数
Matrix partialC2x(const Matrix& x, const Matrix& aims){
    assert(x.col == 1);
    Matrix m(x.row,x.col);
    for (int i = 0; i < x.row; ++i) {
        m.value[i][0] = (x.value[i][0] - aims.value[i][0])/10;  //TODO
    }
    return m;
}

//反向传播
void backPropagation(Matrix& c2w,Matrix& c2x, Matrix& c2b, //对三个量的偏导数
         const Matrix& c2xl,const Matrix& w,const Matrix& x,const Matrix& b){
    c2b = dotProduct(c2xl,dSigma(w*x+b));
    c2x = w.transposition() * c2b;
    c2w = c2b*x.transposition();
}


Matrix toNext(const Matrix &w, const Matrix &x, const Matrix &b) {
    return sigma(w * x - b);
}

Matrix sigma2z(const Matrix& x){
    assert(x.col == 1);
    Matrix z(x.row,x.col);
    for (int i = 0; i < x.row; ++i) {
        double num = x.value[i][0];
        z.value[i][0] = log(num / (1-num))/log(exp(1));
    }
    return z;
}
