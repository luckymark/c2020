//
// Created by asus on 2020/3/15.
//

#ifndef NEURAL_NETWORKS_MATRIX_H
#define NEURAL_NETWORKS_MATRIX_H

void matrix_t(double **a_matrix, const double **b_matrix, int line, int row);
void matrix_a(double **a_matrix, const double **b_matrix, const double **c_matrix,
        int line, int row);
void matrix_m(double **a_matrix, const double **b_matrix, const double **c_matrix,
        int line, int row, int middle);

#endif //NEURAL_NETWORKS_MATRIX_H
