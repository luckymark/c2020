#include <stdio.h>
#define LENGTH 10
void bubbleSort(int *array, int length);

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

void bubbleSort(int *array, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (array[i] > array[j]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}
