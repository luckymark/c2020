#include <stdio.h>
#include <math.h>

int main() {
    int n;
    int flag = 1;
    scanf("%d",&n);
    for(int i=2; i<=sqrt(n); i++){
        if( n%i == 0) {
            flag = 0;
            break;}
    }
    if( flag == 1 ){
        printf("%d是素数",n);
    } else{
        printf("%d不是素数",n);
    }
    return 0;
}
