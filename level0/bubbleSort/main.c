#include <stdio.h>
#include "bubbleSort.h"
#define LENGTH 10

int main(void) {
    int array[LENGTH] = {3, 5, 1, 12, 0, -3, 25, 1, 2, -13};

    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    bubbleSort(array, LENGTH);

    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}