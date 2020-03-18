#include <stdio.h>
#define maxn 1000

int main(void)
{
    char i=2;
    int a[maxn]={0};
    for(i=2;i<=maxn;i++){
        if (a[i-1] == 0){
            int j;
            for(j=2;i*j<=maxn;j++){
                a[i*j-1]=1;
            }
            printf("%d\n",i);
        }
    }
}
