//
// Created by asus on 2020/3/15.
//

#ifndef NEURAL_NETWORKS_NEURAL_NETWORKS_FUNCTIONS_V2_H
#define NEURAL_NETWORKS_NEURAL_NETWORKS_FUNCTIONS_V2_H

#include <stdbool.h>

/**
 * layer def :
 * a = 节点数 * 样本数   a[cur] = g( z[cur] )
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
    double** dz;
    double** dw;
    double* db;
}layer;

/**
 * simple = 10
 * 8*8(L0) --> 16(L1) --> 1(L2)
 * cost function : -( y * log(a) + (1.0 - y) * log(1.0-a) )
 */
#define PIXEL_VALUE (28 * 28)
#define SIMPLE_VALUE 10
#define NODE_L0_VAL PIXEL_VALUE
#define NODE_L1_VAL 16
#define NODE_L2_VAL 16
#define NODE_L3_VAL 10
//#define NODE_L4_VAL 1


void sigmoid_M(double **a, const double **z, int line, int row);
void tanh_M(double **a, const double **z, int line, int row);
void get_z(double** z, const double **w, const double **x, const double *b,
           int cur_layer_node, int last_layer_node);
void get_a(double **a, const double **z, int cur_layer_node, char type);
bool isNULL(layer* player, int cur_layer_node);
double myrand();
void init_layer(layer* player, int cur_layer_node, int last_layer_node);
void del_layer(layer *player, int cur_layer_node);
void get_dz_ReLU(layer* cur_layer,layer* for_layer,int cur_node,int for_node);

#endif //NEURAL_NETWORKS_NEURAL_NETWORKS_FUNCTIONS_V2_H
