#include<stdio.h>
#include <time.h>
#include"GA.h"
#include <windows.h>

player players[PLAYERSNUMBER],sons[PLAYERSNUMBER];
start begin;
end target;
greatest king;
int map[HEIGHT][WIDTH];
int maze[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
HANDLE haut;
COORD coord;

int main()
{
    haut=GetStdHandle(STD_OUTPUT_HANDLE);
    time_t timestart,timeend;
    timestart=clock();
    readinmap();
    printmap();
    printf("\nPlease wait for a moment...");
    initial();
    coord.X=0;
    coord.Y=HEIGHT+2;
    SetConsoleCursorPosition(haut,coord);
    judgethegreat();
    for(int i=1;i<=EVOLUTION;i++)
    {
        coord.X=0;
        coord.Y=HEIGHT+2;
        SetConsoleCursorPosition(haut,coord);
        evolution();
        judgethegreat();
        printf("EVOLUTION %d:The least steps till now is %15d",i,king.steps);
        if(king.adapt==0)
        {
            i--;
            initial();
        }
    }
    printroad();
    timeend=clock();
    double runtime=(double)(timeend-timestart)/CLOCKS_PER_SEC;
    printf("The least steps is:%d\nRunning time:%fs",king.steps,runtime);
    getchar();

    return 0;
}
