#include <stdio.h>

int main(){
    int n;
    do {
        scanf("%d", &n);
    }while(n<=0);
    int flag = 1;
    if (n == 1) flag = 0;
    for (int i = 2; i*i <= n; ++i) {
        if (n % i == 0) {
            flag = 0;
        }
    }
    printf(flag ? "Yes\n" : "No\n");
    return 0;
}