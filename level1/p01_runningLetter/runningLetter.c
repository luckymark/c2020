#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


const int WIDTH = 80;//宽度
const int FRAMES = 30;//帧数

int main(){
    int i = 0;
    int flag = 1;
    while(1) {
        for (int j = 0; j < i; ++j) {
            printf(" ");
        }
        printf("A");
        Sleep(1000 / FRAMES);
        system("CLS");
        if(i == 0) flag = 1;
        if(i == WIDTH - 1) flag = -1;
        i += flag;
    }
}
