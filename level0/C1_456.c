#include <stdio.h>
#include <stdlib.h>
#define MAXN 100000

int a[MAXN];
int main(){
    int n;
    int maxNumber = INT_MIN;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; ++i) {
        if (a[i] > maxNumber){
            maxNumber = a[i];
        }
    }

    printf("The biggest number is %d\n" , maxNumber);
    return 0;
}
