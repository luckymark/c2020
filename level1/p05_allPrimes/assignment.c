#include <stdio.h>
#include <math.h>
#include <time.h>
#define UPPER 1000

/*  质数个数：168
计算次数：
1:78021        原始版本
2:77523        不考虑除去2以外的偶数
3:38678         只判断能否被奇数整除
4:2351          开方后
5:2302          根据合数可以质因数分解的改进
*/

int main(void) {
    int flag = 1;    // 1是质数
    int amount = 1;  //统计质数个数
    unsigned long counter = 0;

    int primeBox[UPPER]={2};

    printf("2\n");

    for (int i = 3; i < UPPER; i += 2, flag = 1) {
        for (int j = 0; primeBox[j] <= sqrt(i); j++) {
            counter++;
            if (i % primeBox[j] == 0) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            amount++;
            printf("%d\n", i);
            primeBox[amount - 1] = i;
        }
    }
    puts("-----------------");
    printf("Seconds:%fs\n",(double)clock()/CLOCKS_PER_SEC );
    printf("amounts of prime=%d\n", amount);
    printf("counter=%lu\n", counter);
    

    return 0;
}