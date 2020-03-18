#include <stdio.h>
#include <math.h>
#define maxn 10000
int isPrime(int n){
    int i;
    for(i=2;i<=sqrt(n);i++){
        if (n%i == 0)
            {return 0;}
    }
    return 1;
} //判断素数

void isG(int n,int* p){
    int j=0;
    int i;
    for (i = 2; i < n; i++) {
        if (*(p+n-2-n%2-i-1) && *(p+i-1)){
            j = 1; break;}//奇数=3+p1+p2,偶数=2+p1+p2
        }
    if (j) {
        printf("%d=%d+%d+%d ture\n",n,2+n%2,i,n-i-2-n%2);}
    else {
        printf("%d flase\n",n);
    }
}  //判断n是否符合哥猜

int main() {
    int i;
    int a[maxn];
    for(i=1;i<=maxn;i++)
        {a[i-1] = isPrime(i);}//获取素数表
    for (int j = 6; j <= maxn; j++) {
        isG(j,a);
    }
    return 0;
}
