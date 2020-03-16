#include <stdio.h>
#include <stdlib.h>
#include "Neural_Networks_Functions_V2.h"

int main()
{
    double **a0 = (double **) malloc(sizeof(double *) * NODE_L0_VAL);
    for (int i = 0; i < NODE_L0_VAL; ++i) {
        a0[i] = (double *) malloc(sizeof(double) * SIMPLE_VALUE);
    }
    layer layer1, layer2;
    init_layer(&layer1, NODE_L1_VAL, NODE_L0_VAL);
    init_layer(&layer2, NODE_L2_VAL, NODE_L1_VAL);

    for (int count = 0; count < 10000; ++count) {
        // L1
        get_z(layer1.z, (const double **) layer1.w, (const double **) a0,
              layer1.b, NODE_L1_VAL, NODE_L0_VAL);
        get_a(layer1.a, (const double **) layer1.z, NODE_L1_VAL);

        //L2
        get_z(layer2.z, (const double **) layer2.w, (const double **) layer1.a,
              layer2.b, NODE_L2_VAL, NODE_L1_VAL);
        get_a(layer2.a, (const double **) layer2.z, NODE_L2_VAL);
    }

    del_layer(&layer1, NODE_L1_VAL);
    del_layer(&layer2, NODE_L2_VAL);
    return 0;
}