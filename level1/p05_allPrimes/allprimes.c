//Eular线性筛法,同时静态分配数组空间
#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#define MAXN 1000

clock_t begin;
bool visited[MAXN+2];
int primes[MAXN+2];

inline void check(int i){ 
    if(0==visited[i]){ 
        //没被筛，是素数
        primes[++primes[0]]=i;
        //更新素数列表
        printf("%d\n",i);
    }
}
void sieve(int i);

int main(){
    begin=clock();
    int i;
    for(i=2;i<=MAXN;++i){ 
        check(i);
        sieve(i);
    }
    printf("total time is %d ms",(1000*(clock()-begin))/CLOCKS_PER_SEC);
}
void sieve(int i){ 
    int j,temp;
    for(j=1;j<=primes[0];++j){ 
        //i作为素数的倍数筛合数
        temp=primes[j]*i;
        if(temp>MAXN)break;
        //素数列表中大小是递增的

        visited[temp]=1;
        //被筛

        if(i%primes[j]==0)break;
        //用最小质因数筛
        //cut off
    }
}
