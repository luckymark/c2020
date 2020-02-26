#include <stdio.h>
#include <stdlib.h>
#define MAXN 10000

int a[MAXN];
int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    while(n--){
        printf("%d ", a[n]);
    }
}
