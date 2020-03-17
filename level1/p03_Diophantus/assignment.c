#include <stdio.h>

int main(void) {
    double a = 1.0 / 6 + 1.0 / 12 + 1.0 / 7;  //结婚前的人生比
    //设丢番图年龄为n  由数学知识 显然有
    double n = 18.0 / (1.0 - 2 * a);
    //最后输出丢番图年龄：
    printf("%d岁", (int)n - 4);
    //然后 再光速逃跑
    return 0;
}
