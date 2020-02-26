#include <stdio.h>
#include <stdlib.h>

int a[10];
int main(){
    for (int i = 0; i < 10; ++i) {
        a[i] = i;
    }
    for (int i = 0; i < 5; ++i) {
        int num;
        scanf("%d", &num);
        a[num] = -1;
    }
    for (int i = 0; i < 10; ++i) {
        if (a[i] >= 0)
            printf("%d ", a[i]);
    }
}
