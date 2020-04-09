#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
struct Matrix{
    int row;
    int col;
    std::vector<std::vector<double> > value{};

    explicit Matrix(int _row = 0, int _col = 0);
    ~Matrix();

    Matrix& operator =(const Matrix& b);
    Matrix operator -()const;

    friend Matrix operator +(const Matrix& a, const Matrix& b);
    friend Matrix operator -(const Matrix& a, const Matrix& b);
    friend Matrix operator *(const Matrix& a, const Matrix& b);
    friend Matrix operator /(const Matrix& a, const double& b);

    Matrix transposition() const;
};

Matrix dotProduct(const Matrix& a, const Matrix& b);
#endif
