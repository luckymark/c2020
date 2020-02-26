#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//返回从开始到结尾的和
long long int sumArray(int* start, int* end){
    long long int sum = 0;
    for (; start <= end; start++) {
        sum += *start;
    }
    return sum;
}

//返回n的阶乘
int factorial(int n){
    if(n < 0)
        return -1;
    if(n == 0 || n == 1)
        return 1;
    return n * factorial(n-1);
}

//返回斐波那契数列的第n个数
int fibonacci(int n){
    if (n<1)
        return -1;
    if (n == 1)
        return 1;
    if (n == 2)
        return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}


int main(){
    printf("%d",fibonacci(5));
}