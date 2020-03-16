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
 * @param a_matrix a_matrix=b_matrix+c_matrix
 * @param line 行数
 * @param row 列数
 * @param control 大于0: 加法  不大于0:减法
 */
void matrix_a(double **a_matrix, const double **b_matrix, const double **c_matrix,
        int line, int row)
{
    int k, k2;

    for (k = 0; k < line; k++)
    {
        for(k2 = 0; k2 < row; k2++)
        {
            a_matrix[k][k2] = b_matrix[k][k2] +  c_matrix[k][k2];
        }
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
    double stmp;

    for (k = 0; k < line; k++)
    {
        for (k2 = 0; k2 < row; k2++)
        {
            stmp = 0.0;
            for (k4 = 0; k4 < middle; k4++)
            {
                stmp += b_matrix[k][k4] * c_matrix[k4][k2];
            }
            a_matrix[k][k2] = stmp;
        }
    }
}