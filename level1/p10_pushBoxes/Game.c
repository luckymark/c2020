//
// Created by pointkab on 2020/3/10.
//
#include <stdio.h>
#include <conio.h>
#include "Game.h"

int N, M;//地图的大小
player player1 = {0, 0, {0,0}};

void Start(FILE*map, int Choice){

    fscanf(map, "%d %d", &N, &M);
    int InfoArray[N][M];
    GetMapInfo(map, InfoArray);
    system("ClS");
    ShowMap(InfoArray);
    Init(InfoArray);
    char Press;
    printf("**上下左右键控制人物走动，ESC键返回**");
    while (IsWin(Choice))
    {
        if((Press = getch())<0) Press=getch();
        fflush(stdin);
        if (Press == 27)
        {
            system("CLS");
            return;
        }
        if(Press==87||Press==119||Press==38||Press==72)
        {
            Move(InfoArray, 0, -1);
        }
        else if(Press==68||Press==100||Press==39||Press==77)
        {
            Move(InfoArray, 1, 0);
        }
        else if(Press==83||Press==115||Press==40||Press==80)
        {
            Move(InfoArray, 0, 1);
        }
        else if(Press==65||Press==97||Press==37||Press==75)
        {
            Move(InfoArray, -1, 0);
        }
        //IsWin(Choice);
    }

}
void Move (int * InfoArray, int x, int y){
    int temp = *(InfoArray + (player1.coord.Y* M) +player1.coord.X);
    int temp1 = *(InfoArray + ((player1.coord.Y + y )* M) +player1.coord.X + x);
    int temp2 = *(InfoArray + ((player1.coord.Y + y*2 )* M) +player1.coord.X + x*2);
    switch (temp1)
    {
        /*箱子*/
        case 2:
            if (temp2 != 2 && temp2 !=1 && temp2 != 3)
            {
                SetPosition(player1.coord.X * 2, player1.coord.Y);
                printf("  ");
                *(InfoArray + ((player1.coord.Y + y )* M) +player1.coord.X + x) = 0;//箱子移动，原来的标识码改变
                player1.coord.X += x;
                player1.coord.Y += y;
                SetPosition((player1.coord.X +x) * 2, player1.coord.Y + y);
                printf("※");
                if (temp2 == -1)
                {
                    *(InfoArray + ((player1.coord.Y + y )* M) +player1.coord.X + x) = 3;
                    player1.Target--;
                }
                else {
                    *(InfoArray + ((player1.coord.Y + y )* M) +player1.coord.X + x) = 2;
                }
                //箱子到了新的地方，该地方标识码变为箱子
                SetPosition(player1.coord.X * 2, player1.coord.Y);
                printf("◎");
                player1.Steps++;
            }
            break;
        case 3:
            if (temp2 != 2 && temp2 !=1 && temp2 != 3)
            {
                SetPosition(player1.coord.X * 2, player1.coord.Y);
                printf("  ");
                *(InfoArray + ((player1.coord.Y + y )* M) +player1.coord.X + x) = -1;//箱子移动，原来的标识码改变
                player1.Target++;
                player1.coord.X += x;
                player1.coord.Y += y;
                SetPosition((player1.coord.X +x) * 2, player1.coord.Y + y);
                printf("※");
                if (temp2 == -1)//如果箱子后面为目标位置
                {
                    *(InfoArray + ((player1.coord.Y + y )* M) +player1.coord.X + x) = 3;
                    player1.Target--;
                }
                else {
                    *(InfoArray + ((player1.coord.Y + y )* M) +player1.coord.X + x) = 2;
                }
                //箱子到了新的地方，该地方标识码变为箱子
                SetPosition(player1.coord.X * 2, player1.coord.Y);
                printf("◎");
                player1.Steps++;
            }
            break;
        default://在地图空白处或目标位置处
            if (temp1 != 1)
            {
                SetPosition(player1.coord.X * 2, player1.coord.Y);
                printf("  ");
                player1.coord.X += x;
                player1.coord.Y += y;
                SetPosition(player1.coord.X * 2, player1.coord.Y);
                printf("◎");
                player1.Steps++;
            }
            break;
    }
    if (temp == -1)
    {
        SetPosition((player1.coord.X - x) * 2, (player1.coord.Y - y));
        printf("□");
    }
    SetPosition(0, N + 1);
    printf("当前你走了 %d 步，还差 %d 个箱子", player1.Steps, player1.Target);
    return;
}
//初始化数据
void Init (const int * InfoArray){
    int i, j;//要推的箱子个数
    player1.coord.X = 0;
    player1.coord.Y = 0;
    player1.Steps = 0;
    player1.Target = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (*(InfoArray + (i * M)+ j) == -1)
                player1.Target++;
            if (*(InfoArray + (i * M) + j) == -3)
            {
                player1.coord.X = j;
                player1.coord.Y = i;
            }
        }
    }
    SetPosition(player1.coord.X * 2, player1.coord.Y);
    printf("◎");
    SetPosition(0, N);
}
//打印菜单
void PrfMenu ()
{
    printf("请选择关卡：\n");
    printf("1-1(简单)\n");
    printf("1-2(困难)\n");
    printf("1-3(变态)\n");
    printf("1-4(地狱)\n");
}
//获取地图具体信息
void GetMapInfo (FILE* map, const int *InfoArray)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            fscanf(map, "%d", InfoArray + i * M +j);
        }
    }
}
//获取关卡
FILE * MapChoice (int Choice)
{
    FILE * map = NULL;
    switch (Choice)
    {
        case 1:
            map = fopen("MapRes.txt", "r");
            break;
        case 2:
            map = fopen("MapRes1.txt", "r");
            break;
        case 3:
            map = fopen("MapRes2.txt", "r");
            break;
        case 4:
            map = fopen("MapRes3.txt", "r");
            break;
    }
    if (map == NULL)
    {
        printf("file to open such file!\n");
    }
    return map;
}
//显示地图
void ShowMap(const int *InfoArray)
{
    int i, j, temp;
    for (i = 0; i < N; i++)
    {
        for (j = 0;j < M; j++)
        {
            temp = *(InfoArray + (i * M) + j);
            switch (temp)
            {
                case 1:
                    printf("■");
                    break;
                case 2:
                    printf("※");
                    break;
                case -1:
                    printf("□");
                    break;
                default:
                    printf("  ");
                    break;
            }
        }
        printf("\n");
    }
}

void SetPosition (int x, int y)
{
    COORD coord ={x, y};
    HANDLE winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(winHandle, coord);
}

int IsWin(int Choice){
    int score;
    char IsCtne;
    if (500 * Choice - player1.Steps < 0)
    {
        score = 0;
    }
    else {
        score = 500 * Choice - player1.Steps;
    }
    if (player1.Target == 0)
    {
        SetPosition(0, N + 2);
        printf("恭喜你，通关！\n你获得了%d分！（是否保存数据？y/n）", score);
        scanf("%c", &IsCtne);
        if (IsCtne == 'Y' || IsCtne == 'y')
        {

            FILE * Save = fopen("Save.txt", "a");
            if (Save == NULL)
            {
                printf("fail to open this file!");
                return;
            }
            fprintf(Save, "游戏记录：\n");
            fprintf(Save, "第%d关：%d分\n", Choice, score);
            fclose(Save);
            printf("记录已保存");
            Sleep(500);
        }
        system("CLS");
        return 0;
    }
    return 1;
}

