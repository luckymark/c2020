#include <stdio.h>
#include <stdlib.h>

int main(){
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= i; ++j) {
            printf("%dX%d=%2d ", j, i, i*j);
        }
        printf("\n");
    }
}
