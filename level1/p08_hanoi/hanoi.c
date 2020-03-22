#include <stdio.h>
int f(int n){
    switch(n){
        case 1:
            return 1;
        case 2:
            return 3;
        default:
            return 2*f(n-1)+1;
    }
}
int main() {
    int n;
    scanf("%d",&n);
    printf("%d",f(n));
    return 0;
}
