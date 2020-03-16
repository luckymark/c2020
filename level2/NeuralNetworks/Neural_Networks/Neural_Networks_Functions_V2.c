//
// Created by asus on 2020/3/15.
//

#include "Neural_Networks_Functions_V2.h"
#include "Matrix.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

void sigmoid_M(double **a, const double **z, int line, int row)
{
    for (int i = 0; i < line; ++i) {
        for (int j = 0; j < row; ++j) {
            a[i][j] = 1.0 / (1.0 + exp(-z[i][j]));
        }
    }
}
void tanh_M(double **a, const double **z, int line, int row)
{
    for (int i = 0; i < line; ++i) {
        for (int j = 0; j < row; ++j) {
            a[i][j] = tanh(z[i][j]);
        }
    }
}
void ReLU(double **a, const double **z, int line, int row)
{
    for (int i = 0; i < line; ++i) {
        for (int j = 0; j < row; ++j) {
            a[i][j] = (z[i][j] > 0) ? z[i][j] : 0; // a[i][j] = max(0, z[i][j]);
        }
    }
}

void get_z(double** z, const double **w, const double **x, const double *b, int cur_layer_node, int last_layer_node)
{
    matrix_m(z, w, x, cur_layer_node, SIMPLE_VALUE, last_layer_node);
    for (int i = 0; i < cur_layer_node; ++i) {
        for (int j = 0; j < SIMPLE_VALUE; ++j) {
            z[i][j] += b[j];
        }
    }
}

void get_a(double **a, const double **z, int cur_layer_node, char type)
{
    switch(type) // choose activation functions
    {
        case 's':
            sigmoid_M(a, z, cur_layer_node, SIMPLE_VALUE);
            break;
        case 't':
            tanh_M(a, z, cur_layer_node, SIMPLE_VALUE);
            break;
        case 'r':
        case 'R':
            ReLU(a,z,cur_layer_node,SIMPLE_VALUE);
            break;
        default:
            printf("Please use right type.\n");
            exit(-2);
    }
}

bool isNULL(layer* player, int cur_layer_node)
{
    bool pd = false;
    if (!player->a || !player->z || !player->w || !player->b || !player->dz || !player->dw || !player->db) {
        pd = true;
    }
    if (!pd) {
        for (int i = 0; i < cur_layer_node; ++i) {
            if (!player->a[i] || !player->z[i] || !player->w[i] || !player->dz[i] || !player->dw[i]) {
                pd = true;
                break;
            }
        }
    }
    return pd;
}

double myrand()
{
    return ( 1.0 * rand() / RAND_MAX ) - 0.5;
}

void init_layer(layer* player, int cur_layer_node, int last_layer_node)
{
    // 分配空间
    player->a = (double **) malloc(sizeof(double *) * cur_layer_node);
    player->z = (double **) malloc(sizeof(double *) * cur_layer_node);
    player->w = (double **) malloc(sizeof(double *) * cur_layer_node);
    player->b = (double *) malloc(sizeof(double) * cur_layer_node);
    player->dz = (double **) malloc(sizeof(double *) * cur_layer_node);
    player->dw = (double **) malloc(sizeof(double *) * cur_layer_node);
    player->db = (double *) malloc(sizeof(double) * cur_layer_node);
    for (int i = 0; i < cur_layer_node; ++i) {
        player->a[i] = (double *) malloc(sizeof(double) * SIMPLE_VALUE);
        player->z[i] = (double *) malloc(sizeof(double) * SIMPLE_VALUE);
        player->w[i] = (double *) malloc(sizeof(double) * last_layer_node);
        player->dz[i] = (double *) malloc(sizeof(double) * SIMPLE_VALUE);
        player->dw[i] = (double *) malloc(sizeof(double) * last_layer_node);
    }

    // 不想判断NULL了.......
    if(isNULL(player,cur_layer_node)) {
        printf("Failed to allocate space.\n");
        exit(-1);
    }

    // 赋值
    srand(time(NULL));

    // 越界
    for (int i = 0; i < cur_layer_node; ++i) {
        player->b[i] = 0.0;
        player->db[i] = 0.0;
        for (int j1 = 0; j1 < SIMPLE_VALUE; ++j1) {
            player->a[i][j1] = 0.0;
            player->z[i][j1] = 0.0;
            player->dz[i][j1] = 0.0;
        }
        for (int j2 = 0; j2 < last_layer_node; ++j2) {
            player->w[i][j2] = 0.02 * myrand();
            player->dw[i][j2] = 0.0;
        }
    }
}

void del_layer(layer *player, int cur_layer_node)
{
    for (int i = 0; i < cur_layer_node; ++i) {
        free(player->a[i]);
        free(player->z[i]);
        free(player->w[i]);
        free(player->dz[i]);
        free(player->dw[i]);
    }
    free(player->a);
    free(player->z);
    free(player->w);
    free(player->b);
    free(player->dz);
    free(player->dw);
    free(player->db);
}
void get_dz_ReLU(layer* cur_layer,layer* for_layer,int cur_node,int for_node)
{
    matrix_t_m(cur_layer->dz,(const double**)for_layer->w,(const double**)for_layer->dz,cur_node,SIMPLE_VALUE,for_node);
    for(int i = 0; i < cur_node; ++i) {
        for(int j = 0; j < SIMPLE_VALUE; ++j) {
            cur_layer->dz[i][j] *= (cur_layer->z[i][j] >= 0)? 1 : 0;
        }
    }
}
