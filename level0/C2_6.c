#include <stdio.h>
#include <stdlib.h>

int main(){
    int sum = 0;
    for (int i = 1; i <= 100; ++i) {
        if (i % 7 == 0 || i % 10 == 7){
            printf("%d ", i);
            sum += i;
        }
    }
    printf("\nsum = %d", sum);
}
