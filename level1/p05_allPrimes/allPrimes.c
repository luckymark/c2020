#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAXN 1000   //最大值

int nextPrime[MAXN + 1];
int main(){
    clock_t start,end;
    start = clock();
    memset(nextPrime,0,sizeof(nextPrime));
    int lastPrime = 2;
    nextPrime[0] = 2;//第一个素数2是唯一的偶数，特殊处理
    printf("%3d,",2);
    for (int i = 3; i <= MAXN; ) {
        int flag = 1;
        for (int u = nextPrime[2]; u*u <= i && u; u = nextPrime[u]) {
            if (i % u == 0){
                flag = 0;
                break;
            }
        }
        if (flag){
            nextPrime[lastPrime] = i;
            lastPrime = i;
            printf("%3d,",i);
        }

        //i的增加方式
        if (i % 2 == 1) i += 2;
        if (i > 10 && i % 5 == 0) i += 2;
    }
    end = clock();
    printf("\n%ld ms", end - start);
    return 0;
}
