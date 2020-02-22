#include <stdio.h>

int main(void) {
    // 100 以内的所有素数（来自 p05）
    int primes[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

    for (int num = 6; num <= 100; num++) {
        int needed = 1; // 每个数字仅需找到一组素数使之成立即可
        for (int i = 0; i < 25 && needed; i++) {
            for (int j = 0; j < 25 && needed; j++) {
                for (int k = 0; k < 25 && needed; k++) {
                    if (num == primes[i] + primes[j] + primes[k]) {
                        printf("%d = %d + %d + %d\n", num, primes[i], primes[j], primes[k]);
                        needed--; // 找到一组数后使该变量为零以跳出循环
                    }
                }
            }
        }
    }

    return 0;
}
