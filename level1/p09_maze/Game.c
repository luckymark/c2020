//
// Created by pointkab on 2020/3/7.
//
#include <stdio.h>
#include "Game.h"
int map[10][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,1,0,0,0,1},
        {1,0,1,1,0,1,0,1,1,1},
        {1,0,0,1,0,1,0,0,0,1},
        {1,1,1,1,0,1,0,1,0,1},
        {1,0,0,0,0,1,0,1,0,1},
        {1,1,1,1,0,0,0,1,0,1},
        {1,1,1,1,1,1,1,1,1,1}
};

player player1 = {0, {2,5}};

void ShowMap()
{
    int i,j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (map[i][j] == 1)
            {
                printf("#");
            }
            else if (map[i][j] == 0)
            {
                printf(" ");
            }
            else {
                printf("P");
            }
        }
        printf("\n");
    }
}
//设置光标
void SetPosition (COORD pos){
    HANDLE winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(winHandle, pos);
}
//游戏开始及初始化
void Start ()
{
    ShowMap();
    SetPosition(player1.coord);
    printf("P");
}
//判断是否到达终点
int IsWin(){
    if (player1.GameStatus == 0)
        return 1;
    return 0;
}
//人物移动
void Move(int x, int y){
    if (player1.coord.X == 0 && player1.coord.Y == 1)
        player1.GameStatus = 1;
    if (map[player1.coord.Y + y][player1.coord.X + x] == 0)
    {
        SetPosition(player1.coord);
        printf(" ");
        player1.coord.X += x;
        player1.coord.Y += y;
        SetPosition(player1.coord);
        printf("P");
    }
}

