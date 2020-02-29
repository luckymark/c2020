#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAXN 1010

bool isprime[MAXN]={0};
int prime[MAXN];

int isPrime(int n){
    int count=0;
    for(int i=2;i<=n;i++){
        if(isprime[i]==0){
            prime[count]=i;count++; //把素数导入数组prime[]
            for(int j=i+i;j<=n;j+=i){
                isprime[j]=1;
            }
        }
    }return count;
}
int main(){
    clock_t start,finish;
    double duration;
    start = clock();

    int num=isPrime(1000);
    for(int i=0;i<num;i++){
        printf("%d ",prime[i]);
    }printf("\n");

    finish = clock();
    duration = (double)(finish-start)/CLOCKS_PER_SEC;//time.h中定义了该常量，一秒钟的计时单元
    printf("%f seconds\n",duration);
    return 0;
}