#include "matrix.h"
#include <cassert>

Matrix::Matrix(int _row, int _col): row(_row),col(_col){
    value.clear();
    for (int i = 0; i < _row; ++i) {
        value.emplace_back();
        for (int j = 0; j < _col; ++j) {
            value[i].emplace_back(0);
        }
    }
}
Matrix::~Matrix() = default;

Matrix& Matrix::operator =(const Matrix& b){
    if(this != &b){
        row = b.row;
        col = b.col;
        value.resize(row);
        for (int i = 0; i < row; ++i) {
            value[i].resize(col);
            for (int j = 0; j < col; ++j) {
                value[i][j] = b.value[i][j];
            }
        }
    }
    return *this;
}

Matrix Matrix::operator -()const {
    Matrix m(row,col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            m.value[i][j] = -value[i][j];
        }
    }
    return m;
}

Matrix Matrix::transposition() const {
    Matrix m(col,row);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            m.value[j][i] = value[i][j];
        }
    }
    return m;
}

Matrix operator +(const Matrix &a, const Matrix &b) {
    assert(a.row == b.row && a.col == b.col);
    int r = a.row,c = b.col;
    Matrix m(r,c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            m.value[i][j] = a.value[i][j] + b.value[i][j];
        }
    }
    return m;
}

Matrix operator *(const Matrix &a, const Matrix &b) {
    assert(a.col == b.row);
    int n = a.col;
    int r = a.row,c = b.col;
    Matrix m(r,c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            double sum = 0;
            for (int p = 0; p < n; ++p) {
                sum += a.value[i][p] * b.value[p][j];
            }
            m.value[i][j] = sum;
        }
    }
    return m;
}

Matrix operator -(const Matrix& a, const Matrix& b) {
    return a + (-b);
}

Matrix operator/(const Matrix &a, const double &b) {
    Matrix m(a.row,a.col);
    for (int i = 0; i < a.row; ++i) {
        for (int j = 0; j < a.col; ++j) {
            m.value[i][j] = a.value[i][j] / b;
        }
    }
    return m;
}

Matrix dotProduct(const Matrix& a, const Matrix& b){
    assert(a.row == b.row && a.col == b.col);
    int r = a.row, c = b.col;
    Matrix m(r,c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            m.value[i][j] = a.value[i][j] * b.value[i][j];
        }
    }
    return m;
}