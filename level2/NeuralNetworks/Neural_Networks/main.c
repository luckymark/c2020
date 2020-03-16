#include <stdio.h>
#include <stdlib.h>
#include "Neural_Networks_Functions_V2.h"
#include "Matrix.h"

int main()
{
    // init a0
    double **a0 = (double **) malloc(sizeof(double *) * NODE_L0_VAL);
    if (!a0) {
        exit(-3);
    }
    for (int i = 0; i < NODE_L0_VAL; ++i) {
        a0[i] = (double *) malloc(sizeof(double) * SIMPLE_VALUE);
        if (!a0[i]) {
            exit(-3);
        }
    }

    //模拟a0初值
    for (int i = 0; i < NODE_L0_VAL; ++i) {
        for (int j = 0; j < SIMPLE_VALUE; ++j) {
            a0[i][j] = myrand();
        }
    }

    // init y
    double **y = (double **) malloc(sizeof(double *) * NODE_L3_VAL);
    if (!y) {
        exit(-3);
    }
    for (int i = 0; i < NODE_L3_VAL; ++i) {
        y[i] = (double *) malloc(sizeof(double) * SIMPLE_VALUE);
        if (!y[i]) {
            exit(-3);
        }
    }

    // 模拟y初值
    for (int i = 0; i < NODE_L3_VAL; ++i) {
        for (int j = 0; j < SIMPLE_VALUE; ++j) {
            y[i][j] = (myrand() > 0) ? 1 : 0;
        }
    }

    // init layer
    layer layer1, layer2, layer3;
    init_layer(&layer1, NODE_L1_VAL, NODE_L0_VAL);
    init_layer(&layer2, NODE_L2_VAL, NODE_L1_VAL);
    init_layer(&layer3, NODE_L3_VAL, NODE_L2_VAL);

    // do
    for (int count = 0; count < 10; ++count) {
        // forward
        {
            // L1
            get_z(layer1.z, (const double **) layer1.w, (const double **) a0,
                  layer1.b, NODE_L1_VAL, NODE_L0_VAL);
            get_a(layer1.a, (const double **) layer1.z, NODE_L1_VAL, 'r');

            // L2
            get_z(layer2.z, (const double **) layer2.w, (const double **) layer1.a,
                  layer2.b, NODE_L2_VAL, NODE_L1_VAL);
            get_a(layer2.a, (const double **) layer2.z, NODE_L2_VAL, 'r');

            // L3
            get_z(layer3.z, (const double **) layer3.w, (const double **) layer2.a,
                  layer3.b, NODE_L3_VAL, NODE_L2_VAL);
            get_a(layer3.a, (const double **) layer3.z, NODE_L3_VAL, 's');
        }

        // back
        {
            // l3
            matrix_a2(layer3.dz, layer3.a, (const double **) y, NODE_L3_VAL, SIMPLE_VALUE, -1);
            matrix_m_t(layer3.dw, (const double **) layer3.dz, (const double **) layer2.a,
                       NODE_L3_VAL, NODE_L2_VAL, SIMPLE_VALUE);
            matrix_sum_per(layer3.db, (const double **) layer3.dz, NODE_L3_VAL, SIMPLE_VALUE);


            // l2
            get_dz_ReLU(&layer2, &layer3, NODE_L2_VAL, NODE_L3_VAL);
            matrix_m_t(layer2.dw, (const double **) layer2.dz, (const double **) layer1.a,
                       NODE_L2_VAL, NODE_L1_VAL, SIMPLE_VALUE);
            matrix_sum_per(layer2.db, (const double **) layer2.dz, NODE_L2_VAL, SIMPLE_VALUE);

            // l1
            get_dz_ReLU(&layer1, &layer2, NODE_L1_VAL, NODE_L2_VAL);
            matrix_m_t(layer1.dw, (const double **) layer1.dz, (const double **) a0,
                       NODE_L1_VAL, NODE_L0_VAL, SIMPLE_VALUE);
            matrix_sum_per(layer1.db, (const double **) layer1.dz, NODE_L1_VAL, SIMPLE_VALUE);

            matrix_a2(layer3.w, layer3.w, (const double **) layer3.dw, NODE_L3_VAL, NODE_L2_VAL, -1);
            matrix_a1(layer3.b, (const double *) layer3.db, NODE_L3_VAL, -1);
            matrix_a2(layer2.w, layer2.w, (const double **) layer2.dw, NODE_L2_VAL, NODE_L1_VAL, -1);
            matrix_a1(layer2.b, (const double *) layer2.db, NODE_L2_VAL, -1);
            matrix_a2(layer1.w, layer1.w, (const double **) layer1.dw, NODE_L1_VAL, NODE_L0_VAL, -1);
            matrix_a1(layer1.b, (const double *) layer1.db, NODE_L1_VAL, -1);
        }
    }


    // del_all
    {
        del_layer(&layer1, NODE_L1_VAL);
        del_layer(&layer2, NODE_L2_VAL);
        del_layer(&layer3, NODE_L3_VAL);
        for (int i = 0; i < NODE_L0_VAL; ++i) {
            free(a0[i]);
        }
        for (int i = 0; i < NODE_L3_VAL; ++i) {
            free(y[i]);
        }
        free(a0);
        free(y);
    }

    return 0;
}