#include <stdio.h>
#include <stdlib.h>

int main(){
    for (int i = 1; i <= 100; ++i) {
        if (i % 3 == 0 && i % 5 != 0){
            printf("%d ", i);
        }
    }
}
