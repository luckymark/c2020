#include <stdio.h>

int main(void) {
    int n;
    int factor = 0;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            factor++;
        }
    }

    if (factor == 2) {
        printf("%d是素数\n", n);
    } else {
        printf("%d不是素数\n", n);
    }

    return 0;
}
