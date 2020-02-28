#include <stdio.h>

int main(){
    for (int i = 1; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                int num = i*100 + j*10 + k;
                if (num == i*i*i + j*j*j + k*k*k){
                    printf("%d ",num);
                }
            }
        }
    }
    return 0;
}
