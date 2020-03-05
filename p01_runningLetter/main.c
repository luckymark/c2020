#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
const int ONESECOND = 1000;
const int FPS = 100;
int WIDTH =50;
int main() {

    CONSOLE_CURSOR_INFO cursor_info={1,0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);

    int i,j=0,direction=1;
    while(1)
    {
        for (i = 0; i <j ; ++i) {
            printf(" ");
        }
        printf("A");
        j+=direction;
        if(j==WIDTH) direction*=-1;
        if(j==0) direction*=-1;
        system("cls");
        Sleep(ONESECOND/FPS);
    }
    return 0;
}
