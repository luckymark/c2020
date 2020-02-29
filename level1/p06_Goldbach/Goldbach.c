#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAXN 100   //最大值


int main(){
    //生成素数数组
    int prime[MAXN/2];
    int p = 0;
    for (int i = 2; i <= MAXN; ++i) {
        int flag = 1;
        for (int j = 2; j*j <= i; ++j) {
            if (i%j == 0){
                flag = 0;
                break;
            }
        }
        if (flag){
            prime[p++] = i;
        }
    }

    int flag = 1;
    for (int i = 4; i < MAXN; i += 2) {
        int u = 0 ,v = p-1;//指向prime开头和结尾,也可以让v指向小于但最接近i的素数
        while(1){
            if(prime[u] + prime[v] == i){
                break;
            }else if(u == v){
                flag = 0;
                break;
            }

            if(prime[u] + prime[v] > i) {
                v--;
                continue;
            }
            if(prime[u] + prime[v] < i){
                u++;
                continue;
            }

        }
        if(!flag) break;
    }

    if (flag) {
        printf("Yes");
    }else{
        printf("No");
    }
    return 0;
}
