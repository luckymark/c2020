#include <math.h>
#include <stdio.h>

int isPrime(int num);
void judger(int n);
void create(int arry[]);

int Dict[100] = {2, 3};  // 质数参考数组默认填充2，3 下标从2开始

//在质数参考数组中存入1~100的质数
void create(int arry[]) {
    int flag = 1;  // 1代表是质数
    int index = 2;

    for (int i = 3; i <= 100; i += 2, flag = 1) {
        for (int j = 3; j <= sqrt(i); j++) {
            if (i % j == 0) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            Dict[index] = i;
            index++;
        }
    }
}

//判断是否为质数
int isPrime(int num) {
    int flag = 1;
    for (int i = 2; i <= sqrt(num); i += flag) {
        if (num % i == 0) {
            return 0;  //不是质数
        }
        if (i == 3 && flag == 1) flag = 2;
    }
    return 1;  //是质数
}

//判断数字n能否被分解为两个质数
void judger(int n) {
    for (int i = 0; Dict[i]<n; i++) {
        if (isPrime(n - Dict[i]) == 1) {
            printf("%d=%d+%d\n",n, Dict[i], n - Dict[i]);
            return;
        }
    }
}

int main(void) {
    create(Dict);
    for (int n = 4; n <= 100; n += 2) {
        judger(n);
    }
    printf("Done!");
    return 0;
}