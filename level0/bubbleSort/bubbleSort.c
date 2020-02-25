#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXN 10000  //数组长度

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int* front, int num) {
    if (front == 0) return;
    if (num <= 0) return;

    for (int i = 1; i < num; i++) {
        for (int j = 0; j < num - i; j++) {
            int* u = front + j;
            int* v = front + j + 1;
            if (*u > *v) swap(u, v);
        }
    }
}

int main() {
    //数组初始化
    int array[MAXN];
    srand((unsigned)time(NULL));
    for (int i = 0; i < MAXN; i++) {
        array[i] = rand();
    }

    //排序，计时
    clock_t start, end;
    start = clock();
    bubbleSort(array, MAXN);
    end = clock();

    //输出排序后数组
    for (int i = 0; i < MAXN; i++) {
        printf("%d ", array[i]);
    }
    //输出所用时间
    printf("\nTake %ld ms", end - start);
    return 0;
}
