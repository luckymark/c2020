#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define BORDER 40

int flag = 1;
int i = 1;  //i指字符所在位置坐标（单坐标），从1开始

int main(void){
    //const int BORDER = 40;

    while(1){
        system("CLS");
        for (int j=1;j<=i;j++){
            printf(" ");
        }
        printf("@");        
        Sleep(1000/50);
        if(i == 1)
            flag = 1;
        if(i==BORDER)
            flag = -1;
        i = i + flag;
    }

    return 0;
}
