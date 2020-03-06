#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * 10000位的最后十个数字
 * 5256375678
 * PI的计算公式 :
 * π/2 = 1 + 1/3 + 1/3 * 2/5 + 1/3 * 2/5 * 3/7 …… + 1*2*3*……n / 3*5*……*(2n+1)
 * =1+1/3(1+2/5(1+……+(n-1)/(2n-1)(1+n/(2n+1))……)
 */

int main() {
    double sum = 0.0;
    int digit, num_items;

    // 读入位数
    printf("\nPlease enter the required number of digits :");
    scanf("%d", &digit);

    // 动态分配数组内存，初始化数组
    int* arr_PI = (int*)malloc(sizeof(int) * (digit + 5));
    if(NULL == arr_PI) {
        printf("Memory allocation failed.\n");
        exit(-1);
    }
    for(int i = 0; i < digit + 5; ++i) {
        arr_PI[i] = 0;
    }

    // 累加确定项数 -- num_items
    for(num_items = 1; sum <= digit + 1; ++num_items) {
        sum += log10((2.0 * num_items + 1) / num_items);
    }

    // 按公式分布计算
    int divisor = num_items * 2 + 1; // 分母位置（除数）
    int molecule = 1; // 分子位置（被除数）
    int round_num = 0; //进位数

    for(int cur_item = num_items; cur_item > 0; --cur_item, divisor -= 2) {
        // 各位 除  divisor(2 * cur_item + 1)
        for(int i = 0; i < digit + 5; ++i) {
            arr_PI[i] = molecule / divisor;
            molecule = (molecule % divisor) * 10 + arr_PI[i + 1];
        }
        arr_PI[digit + 5] = molecule / divisor;

        // 各位乘 cur_item
        round_num = 0;
        for(int i = digit + 5; i >= 0; --i) {
            arr_PI[i] = arr_PI[i] * cur_item + round_num;
            round_num = arr_PI[i] / 10;
            arr_PI[i] = arr_PI[i] % 10;
        }
        arr_PI[0] = arr_PI[0] + 1;
        molecule = arr_PI[0]; // 整数加 1
    }

    // 按公式各位乘2
    round_num = 0;
    for(int i = digit + 5; i >= 0; --i) {
        arr_PI[i] = arr_PI[i] * 2 + round_num;
        round_num = arr_PI[i] / 10;
        arr_PI[i] = arr_PI[i] % 10;
    }

    // 输出计算结果
    int count = 0;
    printf("\nPI = %d.\n", arr_PI[0]);
    for(int i = 1; i <= digit; i++) {
        printf("%d", arr_PI[i]);
        // 打印间隔符
        if(i % 10 == 0) {
            printf("  ");
            if(i % 50 == 0) {
                printf("// %3d\n", ++count);
            }
        }
    }
    printf("\n");

    // 释放内存
    free(arr_PI);

    return 0;
}

