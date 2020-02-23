// 采用欧拉筛法，极大优化算法效率
#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX 1001

int main() {
    int flag[MAX];
    int primes[MAX];
    int totPrimes = 0;
    clock_t start, end;

    start = clock();
    memset(flag, 0, sizeof(flag));

    for (int i = 2; i < MAX; i++) {
        if (!flag[i]) {
            primes[totPrimes++] = i;
            printf("%d\n", i);
        }

        for (int j = 0; i * primes[j] < MAX; j++) {
            flag[i * primes[j]] = 1;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
    end = clock();
    printf("%.1fms", (float)(end - start) / CLOCKS_PER_SEC * 1000);

    return 0;
}
