#include <stdio.h>
#include <time.h>
int is_prime(int x);

int main(void) {
    clock_t start, finish;

    start = clock();
    for (int i = 2; i <= 1000; i++) {
        if (is_prime(i)) {
            printf("%d\n", i);
        }
    }
    finish = clock();
    printf("计算所用时间: %.1f ms\n", ((float)(finish - start) / CLOCKS_PER_SEC * 1000));
}

int is_prime(int x) {
    int factor = 0;

    for (int i = 1; i <= x; i++) {
        if (x % i == 0) {
            factor++;
        }
    }

    if (factor == 2) {
        return 1;
    }

    return 0;
}
