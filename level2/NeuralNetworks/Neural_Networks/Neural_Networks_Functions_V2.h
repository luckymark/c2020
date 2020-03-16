//
// Created by asus on 2020/3/15.
//

#ifndef NEURAL_NETWORKS_NEURAL_NETWORKS_FUNCTIONS_V2_H
#define NEURAL_NETWORKS_NEURAL_NETWORKS_FUNCTIONS_V2_H

#include <stdbool.h>

/**
 * layer def :
 * a = 节点数 * 样本数   a[cur] = sigmoid( z[cur] )
 * z = 节点数 * 样本数   z[cur] = w[cur] * a[last] + b[cur]
 * w = 节点数 * 上层节点数
 * b = 节点数 * 样本数 (每个样本的b都是一样的向量)
 * --> b = 1 * 节点数 (换成一位数组)
 */
typedef struct __layer__ {
    double** a;
    double** z;
    double** w;
    double* b;
}layer;

/**
 * simple = 10
 * 8*8(L0) --> 16(L1) --> 1(L2)
 */
#define PIXEL_VALUE (8 * 8)
#define SIMPLE_VALUE 10
#define NODE_L0_VAL PIXEL_VALUE
#define NODE_L1_VAL 16
#define NODE_L2_VAL 1

void sigmoid_M(double **a, const double **z, int line, int row);
void get_z(double** z, const double **w, const double **x, const double *b,
           int cur_layer_node, int last_layer_node);
void get_a(double **a, const double **z, int cur_layer_node);
bool isNULL(layer* player, int cur_layer_node);
void init_layer(layer* player, int cur_layer_node, int last_layer_node);
void del_layer(layer *player, int cur_layer_node);

#endif //NEURAL_NETWORKS_NEURAL_NETWORKS_FUNCTIONS_V2_H
