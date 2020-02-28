#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//辅助函数
int is_between(int x,int a, int b){
    if((a-x) * (b-x) > 0){
        return 0;
    }else{
        return 1;
    }
}

int is_cross(int a0,int a1,int b1,int b2){
    int flag =  is_between(b2,a0,a1) + is_between(b1,a0,a1);
    return flag;
}

//1 返回从开始到结尾的和
long long int sumArray(int* start, int* end){
    long long int sum = 0;
    for (; start <= end; start++) {
        sum += *start;
    }
    return sum;
}

//2 返回n的阶乘
int factorial(int n){
    if(n < 0)
        return -1;
    if(n == 0 || n == 1)
        return 1;
    return n * factorial(n-1);
}

//3 返回斐波那契数列的第n个数
int fibonacci(int n){
    if (n<1)
        return -1;
    if (n == 1)
        return 1;
    if (n == 2)
        return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

//4 判断是否为直角三角形
int is_rt(int a,int b, int c){
    if (a<=0 || b<=0 || c<= 0){
        return 0;
    }
    if (a*a + b*b == c*c){
        return 1;
    }
    if (a*a + c*c == b*b){
        return 1;
    }
    if (b*b + c*c == a*a){
        return 1;
    }
}

//5 判断两个矩形是否重叠
int is_cover(int ax0,int ay0,int ax1,int ay1,int bx0,int by0,int bx1, int by1){
    int flag1 = is_cross(ax0,ax1,bx0,bx1) + is_cross(bx0,bx1,ax0,ax1);
    int flag2 = is_cross(ay0,ay1,by0,by1) + is_cross(by0,by1,ay0,ay1);
    if (flag1 && flag2){
        return 1;
    }else{
        return 0;
    }
}

//6 美元换算成人民币
float USD_to_CNY(float USD){
    return 6.98 * USD;
}

int main(){
    printf("%d",is_cover(2,2,10,10,3,3,4,4));

}