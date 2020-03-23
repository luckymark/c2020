#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
const int WIDE =70;
const int FPS =60;
int main()
{
    int a=0,b=1,c;
    while(1)
    {
        for(c=0;c<a;c++)
        {
            printf(" ");
        }
        printf("catch me~");
        Sleep(1000/FPS);
        system("CLS");
        a += b;
        if(a==WIDE){b=-1;}
        if(a==0){b=1;}
    }
}