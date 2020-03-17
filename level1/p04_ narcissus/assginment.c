#include <stdio.h>
#define BA 10

void narcissus(int n);

int pow(int a, int b);//a的b次方

int pow(int a, int b) {
    int c = 1;
    for (int i = 1; i <= b; i++) {
        c *= a;
    }
    return c;
}

void narcissus(int n) {
    int a, b, c;// 百，十，个
    int num;
    for (int i = pow(BA, n-1); i < pow(BA, n); i++) {
        a = i / 100;
        b = (i / 10) % 10;
        c = i % 10;
        num = pow(a, n) + pow(b,n) + pow(c,n);
        if (i == num) printf("%d\n", i);
    }
}

int main(void) {
    narcissus(3); //输出3位水仙花数
    return 0; }