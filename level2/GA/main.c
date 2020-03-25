#include<stdio.h>
#include <time.h>
#include"GA.h"

player players[PLAYERSNUMBER],sons[PLAYERSNUMBER];
start begin;
end target;
greatest king;
int map[HEIGHT][WIDTH];
int maze[4][2]={{-1,0},{0,-1},{1,0},{0,1}};

int main()
{
    time_t timestart,timeend;
    timestart=clock();
    readinmap();
    printmap();
    printf("\nPlease wait for a moment...");
    initial();
    judgethegreat();
    for(int i=1;i<=EVOLUTION;i++)
    {
        evolution();
        judgethegreat();
    }
    printroad();
    timeend=clock();
    double runtime=(double)(timeend-timestart)/CLOCKS_PER_SEC;
    printf("The least steps is:%d\nRunning time:%fs",king.steps,runtime);
    getchar();

    return 0;
}
