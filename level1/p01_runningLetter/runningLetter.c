#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


int main() {
    int i=1;
    while(1) {
        int j = 0;
        for(;j<100-abs((i%(200))-100);++j)  //绝对值函数和模函数组合
            printf(" ");
        printf("A\n");
        Sleep(1.0/60);
        i++;
        system("CLS");
    }
}