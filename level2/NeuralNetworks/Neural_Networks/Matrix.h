//
// Created by asus on 2020/3/15.
//

#ifndef NEURAL_NETWORKS_MATRIX_H
#define NEURAL_NETWORKS_MATRIX_H

void matrix_t(double **a_matrix, const double **b_matrix, int line, int row);
void matrix_a2(double **a_matrix, double **b_matrix, const double **c_matrix, int line, int row, int type);
void matrix_a1(double *a_matrix, const double *c_matrix, int row, int type);
void matrix_m(double **a_matrix, const double **b_matrix, const double **c_matrix,
        int line, int row, int middle);
void matrix_M(double **a_matrix, double **b_matrix, const double **c_matrix, int line, int row);
void matrix_m_t(double **a_matrix, const double **b_matrix, const double **c_matrix, int line, int row, int middle);
void matrix_t_m(double **a_matrix, const double **b_matrix, const double **c_matrix, int line, int row, int middle);
void matrix_sum_per(double *a_matrix, const double **b_matrix, int line, int row);

#endif //NEURAL_NETWORKS_MATRIX_H
