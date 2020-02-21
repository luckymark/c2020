#include <stdio.h>

int main(void) {
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                if (100 * i + 10 * j + k == i * i * i + j * j * j + k * k * k) {
                    printf("%d%d%d\n", i, j, k);
                }
            }
        }
    }

    return 0;
}
