#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define TIME 60 //帧数
#define WIDTH 120 //宽度
#define ONESECOND 1000 //一秒

int main() {
    int i = 0; int s = 1;
    while (1)
    {
        for (int k = 0; k < i; k++)
        {
            printf(" ");
        }
        printf("a");
        Sleep(ONESECOND / TIME);

        system("cls");
        if (i == 0)s = 1;
        if (i == WIDTH - 1)s = -1;
        i += s;

    }
    return 0;
}
