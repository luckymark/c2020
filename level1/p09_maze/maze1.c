#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"maze.h"

extern void open(void);
extern void putmap(void);
extern int startgame(void);

int main()
{
    int judge;               // 判断是否退出游戏。
    open();					 // 把文件信息传入数组中。
    putmap();				 // 输出显示的迷宫。
    judge=startgame();       // 开始游戏。
    if (1 == judge)
    {
        printf("You have quited the game!");
        getchar();
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("    Congratulate!");
    }
    getchar();
    return 0;
}

