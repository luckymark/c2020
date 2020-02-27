#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
const int WIDTH=120;
const int FPS=60;
const int ONESECOND=1000;
int main()
{
    int frontspace=0;
    int change=1;
    while(1)
    {
        for(int i=0;i<frontspace;i++) printf(" ");
        printf("A");
        Sleep(ONESECOND/FPS);
        system("CLS");
        if(frontspace==WIDTH-1) change=-1;
        if(frontspace==0) change=1;
        frontspace+=change;
    }
    return 0;
}
