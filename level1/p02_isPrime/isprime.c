#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){ 
    int n;
    scanf("%d",&n);
    //number to check

    int *prime=(int*)malloc(sizeof(int)*(n+2));
    int *visit=(int*)malloc(sizeof(int)*(n+2)); 
    //prime array consists of the primes
    //visit array is used to check

    memset(prime,0,sizeof(int)*(n+2));
    memset(visit,0,sizeof(int)*(n+2));
    
    int i=2;
    //1既不是素数也不是合数
    int temp;
    
    while(i<=n/2){ 
        //最小质因数筛法,第n个数如果被筛，肯定是被前n/2个数筛掉的
        if(visit[i]==0){ 
            //没被筛的情况，素数
            prime[++prime[0]]=i;
            //更新素数列表
        }

        int j;
        for(j=1;j<=prime[0];++j){ 
            //i作为素数的倍数筛合数
            temp=prime[j]*i;
            if(temp>n)break;
            //列表是递增的

            visit[temp]=1;
            if(temp==n)goto ans;
            //被检测数已经被筛
            if(i%prime[j]==0)break;
            //用最小质因数筛

        }
        ++i;
    }

    //最终未被筛除
    puts("Yes");
    return 0;
ans:
    //n被筛
    puts("No");
    return 0;
}

