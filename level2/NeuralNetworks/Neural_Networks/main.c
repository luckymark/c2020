#include <stdio.h>
#include <stdlib.h>
#include "Neural_Networks_Functions.h"

int main()
{
    // input-output layer
    sample samples1[SIMPLE_SIZE];
    for(int i = 0; i < SIMPLE_SIZE; ++i) {
        init_simple(&samples1[i],NUM_INPUT_NODE);
    }
    node nodes[NUM_OUTPUT_NODE];
    for(int i = 0; i < NUM_OUTPUT_NODE; ++i) {
        init_node(&nodes[i], SIMPLE_SIZE, NUM_INPUT_NODE, samples1);
    }

    for (int count = 0; count < 1000; ++count) {
        for(int i = 0; i < NUM_OUTPUT_NODE; ++i) {
            train_node(&nodes[i], NUM_INPUT_NODE);
        }
    }

    return 0;
}

