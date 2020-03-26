//
// Created by surfaceCS on 2020/3/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "GA.h"

extern int map[HEIGHT][WIDTH];
extern start begin;
extern end target;
extern greatest king;
extern player players[PLAYERSNUMBER],sons[PLAYERSNUMBER];
extern int map[HEIGHT][WIDTH];
extern int maze[4][2];
extern COORD coord;
extern HANDLE haut;

void initial(void)
{
    srand((unsigned)(time(NULL)));
    for (int i = 0; i < PLAYERSNUMBER; ++i)
    {
        for (int j = 0; j < GENELENGTH; ++j)
            players[i].gene[j]=rand()%4;
    }
}

void readinmap(void)
{
    FILE* fp;
    char str[WIDTH+1];
    fp=fopen("map.txt","r");
    for(int i=0;i<HEIGHT;i++)
    {
        fscanf(fp,"%s",str);
        for(int j=0;j<WIDTH;j++)
        {
            switch (str[j])
            {
                case '0':
                    map[i][j]=0;
                    break;
                case '1':
                    map[i][j]=1;
                    break;
                case '2':
                    begin.x=i;
                    begin.y=j;
                    map[i][j]=0;
                    break;
                case '3':
                    target.x=i;
                    target.y=j;
                    map[i][j]=3;
                    break;
                default:
                    break;
            }
        }
    }
    fclose(fp);
}

void printmap(void)
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            if(map[i][j]==1)
                printf("#");
            else if(map[i][j]==0)
                printf(" ");
            else
                printf("O");
        }
        printf("\n");
    }
}

int cmp(const void*a,const void*b)
{
    return ((player *)b)->adapt-((player *)a)->adapt;
}

void evolution(void)
{
    srand((unsigned)(time(NULL)));
    int sonsum=0;
    sons[0].adapt=0;
    for (int i = 0; i < PLAYERSNUMBER; ++i)
    {
        if(players[i].adapt>sons[0].adapt)
        {
            sons[sonsum]=players[i];
        }
    }
    if(sons[0].adapt!=0)
        sonsum++;
    qsort(players,PLAYERSNUMBER, sizeof(player),cmp);
    for (; sonsum<PLAYERSNUMBER ; ++sonsum)
    {
        int dad=rand()%FATHER;
        int mom=rand()%FATHER;
        int temp=rand()%GENELENGTH;
        for (int i = 0; i < temp; ++i)
        {
            sons[sonsum].gene[i]=players[dad].gene[i];
        }
        for (int k = temp; k < GENELENGTH; ++k)
        {
            sons[sonsum].gene[k]=players[mom].gene[k];
        }
    }
    for (int k = 0; k < PLAYERSNUMBER; ++k)
    {
        players[k]=sons[k];
    }
}

void judgethegreat(void)
{
    for (int i = 0; i < PLAYERSNUMBER; ++i)
    {
        int steps=0;
        players[i].x=begin.x;
        players[i].y=begin.y;
        players[i].adapt=0;
        for (int j = 0; j < GENELENGTH; ++j)
        {
            if(map[players[i].x+maze[players[i].gene[j]][0]][players[i].y+maze[players[i].gene[j]][1]]==0)
            {
                players[i].x=players[i].x+maze[players[i].gene[j]][0];
                players[i].y=players[i].y+maze[players[i].gene[j]][1];
                players[i].adapt-=10;
                steps++;
            }
            else if (map[players[i].x+maze[players[i].gene[j]][0]][players[i].y+maze[players[i].gene[j]][1]]==3)
            {
                players[i].adapt+=10000;
                steps++;
                break;
            }
        }
        if(players[i].adapt>=king.adapt)
        {
            king.num=i;
            king.steps=steps;
            king.adapt=players[i].adapt;
        }
    }
}

void printroad(void)
{
    int steps=1;
    players[king.num].x=begin.x;
    players[king.num].y=begin.y;
    for (int i = 0; i < GENELENGTH ; ++i)
    {
        coord.Y=players[king.num].x;
        coord.X=players[king.num].y;
        SetConsoleCursorPosition(haut,coord);
        printf("a");
        if(map[players[king.num].x+maze[players[king.num].gene[i]][0]][players[king.num].y+maze[players[king.num].gene[i]][1]]==0)
        {
            players[king.num].x+=maze[players[king.num].gene[i]][0];
            players[king.num].y+=maze[players[king.num].gene[i]][1];
            steps++;
        }
        else if (map[players[king.num].x+maze[players[king.num].gene[i]][0]][players[king.num].y+maze[players[king.num].gene[i]][1]]==3)
        {
            coord.Y=target.x;
            coord.X=target.y;
            SetConsoleCursorPosition(haut,coord);
            printf("a");
            break;
        }
        coord.X=0;
        coord.Y=HEIGHT+3;
        SetConsoleCursorPosition(haut,coord);
        printf("%d",steps);
        Sleep(100);
    }
    coord.Y=HEIGHT+4;
    coord.X=0;
    SetConsoleCursorPosition(haut,coord);
}

