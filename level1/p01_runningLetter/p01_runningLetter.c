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
<<<<<<< HEAD
        if(a==WIDE){b=-1;}
        if(a==0){b=1;}
=======
        if(a==WIDE)
        {
            b=-1;
        }
        if(a==0)
        {
            b=1;
        }
>>>>>>> d8d4165c6d1a6c4d5aa568cac24ba154e3e7026c
    }
}