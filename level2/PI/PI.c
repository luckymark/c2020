#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
// #include <Psapi.h>   //发现要用这东西得安个包
#define LENGTH 10010    //数组长度
#define ACCURACY 10000  //精度

int main() {
    // HANDLE handle=GetCurrentProcess();
    // PROCESS_MEMORY_COUNTERS pmc;
    // GetProcessMemoryInfo(handle,&pmc,sizeof(pmc));

    //所用公式 pi/2 = 1 + 1/3 + 1/3 * 2/5 + 1/3 * 2/5 * 3/7 + ...
    //优点：迭代可以使用之前计算过的数，代码好实现
    //缺点：收敛速度大概2~3次精度加1位；因为要使用之前的数所以没法多线程
    time_t startTime = clock();
    short pi[LENGTH];  //储存pi
    short xn[LENGTH];  //每次迭代的数值，xn的值会越来越小，
                       //当xn第一个非0的值的位置高于精度，就不用继续迭代

    memset(pi, 0, sizeof(pi));
    memset(xn, 0, sizeof(xn));
    pi[1] = 2;
    xn[1] = 2;

    int d = 1;  //精度位置
    int count = 0;
    int i = 1, n = 3;
    while (1) {
        //计算xn*i
        count++;
        int temp = 0;  //储存进位
        for (int p = LENGTH - 1; p > 0; --p) {
            if (p < d && temp == 0) {
                break;
            }
            int ans = xn[p] * i + temp;
            xn[p] = ans % 10;
            temp = ans / 10;
        }

        //计算xn/n
        temp = 0;  //储存前面的数字，可以被除就会减少
        for (int p = 1; p < LENGTH; ++p) {
            int ans = xn[p] + temp * 10;
            xn[p] = ans / n;
            temp = ans % n;
        }

        //找一下xn中非0的位置
        for (int p = d;; ++p) {
            if (xn[p] != 0) {
                d = p;
                break;
            }
        }
        if (d > ACCURACY) {
            break;
        }

        //计算pi+xn
        for (int p = LENGTH - 1; p >= d; --p) {
            short ans = pi[p] + xn[p];
            pi[p] = ans % 10;
            pi[p - 1] += ans / 10;
        }
        temp = d - 1;  //暂时拿来当指针
        while (pi[temp] / 10) {
            short ans = pi[temp];
            pi[temp--] = ans % 10;
            pi[temp] += ans / 10;
        }

        i++;
        n += 2;
    }

    printf("%d.", pi[1]);
    for (int p = 2; p <= 10000; ++p) {
        printf("%d", pi[p]);
    }
    printf("\nNumber of iterations: %d\n", count);
    printf("Cost time: %lld s\n", (clock() - startTime) / CLOCKS_PER_SEC);
    // printf("Cost memory: %lld\n",pmc.PeakWorkingSetSize);
}
