#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define SCREEN_WIDTH 40
#define SECOND 1000
#define FRAME_NUM 24
int main() {
    int ctrNum1 = 1;
    int ctrNum2 = 1;
    int *ptr = &ctrNum1;
    int i = 0;
    while(1)
    {
        while(i < *ptr)
        {
            printf(" ");
            i++;
        }
        printf("a");
        Sleep(SECOND/FRAME_NUM);
        system("cls");
        if (*ptr == SCREEN_WIDTH-1 && ptr == &ctrNum1)//选择判断空格的增减
        {
            ptr = &ctrNum2;
        }
        if (*ptr == 0 && ptr == &ctrNum2)
        {
            ptr = &ctrNum1;
        }
        if (i ==*ptr && ptr ==&ctrNum1)
        {
            i = 0;
            ctrNum1++;
            ctrNum2++;
        }
        if (i ==*ptr && ptr == &ctrNum2)
        {
            i = 0;
            ctrNum1--;
            ctrNum2--;
        }
    }
    return 0;
}
