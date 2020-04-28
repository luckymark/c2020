#include <stdio.h>
#include <time.h>
#include <string.h>

#define maxn 1000

int main()
{
    int prime[maxn];
    int Prime[maxn];
    memset(prime,0,sizeof(int)*maxn);
    int tail = -1;
    clock_t start,finish;
    start = clock();
    //欧拉筛
    for(int i=2;i<=maxn ;i++){
        if(prime[i]==0){
            Prime[++tail] = i;}
        for(int j=0;j<=tail;j++ ){
                if(i*Prime[j]>maxn) {break;}
                prime[i*Prime[j]]=1;
                if((i%Prime[j]) == 0) {break;}
        }
    }
    //
    printf("2是素数\n");
    for(int k=0;k<=tail;k++){
        printf("%d\n", Prime[k]);
    }
    finish = clock();
    double time = (double)(finish-start)/CLOCKS_PER_SEC;
    printf("时间是%0.3fs",time);
}