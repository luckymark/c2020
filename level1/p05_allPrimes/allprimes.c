#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#define MAXN 1000
clock_t beg;
bool visit[MAXN+2];
int prime[MAXN+2];
int main(){
    beg=clock();
    int i=2;
    int temp;
    while(i<=MAXN){ 
        //第n个数如果被筛肯定是被前n/2个数筛掉的
        if(visit[i]==0){ 
            //没被筛的情况，素数
            prime[++prime[0]]=i;
            printf("%d\n",i);
            //更新素数列表
        }

        int j;
        for(j=1;j<=prime[0];++j){ 
            //i作为素数的倍数筛合数
            temp=prime[j]*i;
            if(temp>MAXN)break;
            //列表是递增的

            visit[temp]=1;
            //被筛
            
            if(i%prime[j]==0)break;
            //用最小质因数筛
            //注意这三条语句的位置关系 
        }
        ++i;
    }
    printf("total time is %d ms",clock()-beg);
}

//直接线性筛法,同时静态分配数组空间
