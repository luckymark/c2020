#include <stdio.h>
#include <string.h>

int array[1000];                  //千位数字
unsigned long long int time = 0;  //操作次数

//移动n个圆盘
void move(const int n) {
    time++;  //移动自身
    if (n == 1) {
        return;
    }
    move(n - 1);  //移动上面n-1
    move(n - 1);  //移回上面n-1
}

// a的n次幂,返回有效数组的长度
int power(int a, int n) {
    memset(array, 0, sizeof(array));
    int p = 1;
    array[0] = 1;
    while (n--) {
        int p0 = p;
        while (p--) {
            int num = array[p] * a;
            array[p] = num % 10;
            array[p + 1] += num / 10;
        }
        if (array[p0]) {
            p = p0 + 1;
        } else {
            p = p0;
        }
    }
    return p;
}

int main() {
    int n;  //圆盘数量
    //  move(n);  //64个圆盘时用函数速度过慢
    printf("How many discs are there?\n");
    scanf("%d", &n);
    printf("Number of moves:\n");
    int p = power(2, n);
    while (p--) {
        printf("%d", p ? array[p] : array[p] - 1);  // 2的n次方结尾不可能是0
    }
    return 0;
}
