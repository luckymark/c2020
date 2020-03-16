//
// Created by asus on 2020/3/15.
//

#include "Matrix.h"
/**
 *
 * @param a_matrix 转置后的矩阵
 * @param b_matrix 转置前的矩阵
 * @param line 行数
 * @param row 列数
 */
void matrix_t(double **a_matrix, const double **b_matrix, int line, int row)
{
    int k, k2;

    for (k = 0; k < line; k++)
    {
        for(k2 = 0; k2 < row; k2++)
        {
            a_matrix[k2][k] = b_matrix[k][k2];
        }
    }
}
/**
 * 
 * @param a_matrix a_matrix = b_matrix + c_matrix
 * @param line 行数
 * @param row 列数
 * @param type 大于0: 加法  不大于0:减法
 */
void matrix_a2(double **a_matrix, double **b_matrix, const double **c_matrix, int line, int row, int type)
{
    for (int i = 0; i < line; i++)
    {
        for(int j = 0; j < row; j++)
        {
            a_matrix[i][j] = b_matrix[i][j] + ((type > 0) ? c_matrix[i][j] : -c_matrix[i][j]);
        }
    }
}
void matrix_a1(double *a_matrix, const double *c_matrix, int row, int type)
{
    for(int i = 0; i < row; ++i) {
        a_matrix[i] += ((type > 0) ? c_matrix[i] : -c_matrix[i]);
    }
}
/**
 *
 * @param a_matrix a_matrix = b_matrix * c_matrix
 * @param line 行数
 * @param row 列数
 * @param middle 第一个矩阵的列数 或者 第二个矩阵的行数
 */
void matrix_m(double **a_matrix, const double **b_matrix, const double **c_matrix, int line, int row, int middle)
{
    int k, k2, k4;
    double temp;

    for (k = 0; k < line; k++)
    {
        for (k2 = 0; k2 < row; k2++)
        {
            temp = 0.0;
            for (k4 = 0; k4 < middle; k4++)
            {
                temp += b_matrix[k][k4] * c_matrix[k4][k2];
            }
            a_matrix[k][k2] = temp;
        }
    }
}
/**
 *
 * @param a_matrix  a_matrix = b_matrix .* c_matrix;
 * @param line 行数
 * @param row 列数
 */
void matrix_M(double **a_matrix, double **b_matrix, const double **c_matrix, int line, int row)
{
    for (int i = 0; i < line; i++)
    {
        for (int j = 0; j < row; j++)
        {

            a_matrix[i][j] = b_matrix[i][j] * c_matrix[i][j];
        }
    }
}
/**
 *
 * @param a_matrix a_matrix = b_matrix * c_matrix^T;
 * @param line
 * @param row
 */
void matrix_m_t(double **a_matrix, const double **b_matrix, const double **c_matrix, int line, int row, int middle)
{
    double temp;
    for(int i = 0; i < line; ++i) {
        for(int j = 0; j < row; ++j) {
            temp = 0.0;
            for(int k = 0; k < middle; ++k) {
                temp += b_matrix[i][k] * c_matrix[j][k];
            }
            a_matrix[i][j] = temp;
        }
    }
}
void matrix_sum_per(double *a_matrix, const double **b_matrix, int line, int row)
{
    double temp;
    for(int i = 0;i < line; ++i) {
        temp = 0.0;
        for(int j = 0; j < row; ++j) {
            temp += b_matrix[i][j];
        }
        a_matrix[i] = temp / row;
    }
}
void matrix_t_m(double **a_matrix, const double **b_matrix, const double **c_matrix, int line, int row, int middle)
{
    double temp;
    for(int i = 0; i < line; ++i) {
        for(int j = 0; j < row; ++j) {
            temp = 0.0;
            for(int k = 0; k < middle; ++k) {
                temp += b_matrix[k][i] * c_matrix[k][j];
            }
            a_matrix[i][j] = temp;
        }
    }
}