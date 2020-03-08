#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
//设置迷宫长宽，墙和路径的值，RANK调整挖墙深度
#define  L 30
#define W 30
#define WALL 0
#define ROUTE 1
#define PERSON -1
int RANK = 5;

int direction[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int maze[L+5][L+5];
int finalx,finaly;

//初始化迷宫
void initmaze(){
    memset(maze,WALL, sizeof(maze));
    for (int i = 0; i <L ; ++i) {
        maze[0][i] = ROUTE;
        maze[i][0] = ROUTE;
        maze[L-1][i] = ROUTE;
        maze[i][L-1] = ROUTE;
    }
}

//开始生成迷宫
void mazego(int x,int y)
{
    maze[x][y]=ROUTE;
    int temp,r;
    for (int i = 0; i <4 ; ++i)
    {
        r = rand()%4;
        temp=direction[0][0];
        direction[0][0]=direction[r][0];
        direction[r][0]=temp;
        temp=direction[0][1];
        direction[0][1]=direction[r][1];
        direction[r][1]=temp;
    }
    int dx,dy,range,cnt;
    for (int i = 0; i <4 ; ++i)
    {
        dx=x;
        dy=y;
        range =1 + (RANK==0 ? 0 : rand()%RANK);
        while(range>0)
        {
            dx+=direction[i][0];
            dy+=direction[i][1];
            if(maze[dx][dy]==ROUTE) break;

            cnt=0;
            if(maze[dx+1][dy]==ROUTE) cnt++;
            if(maze[dx-1][dy]==ROUTE) cnt++;
            if(maze[dx][dy+1]==ROUTE) cnt++;
            if(maze[dx][dy-1]==ROUTE) cnt++;

            if(cnt>1)
                break;
            range--;
            maze[dx][dy]=ROUTE;
        }
        if(range<=0)
        {
            mazego(dx,dy);
        }

    }
}
//画迷宫出口
void complemaze()
{
    maze[2][1]=ROUTE;
    for (int i = L-3; i>=0 ; i--) {
        if(maze[i][L-3]==ROUTE){
            maze[i][L-2]=ROUTE;
            finalx=i;
            finaly=L-2;
            break;
        }
    }
}
//打印迷宫
void printmaze()
{
    for(int i=1;i <L-1;++i) {
        for (int j = 1; j <L-1 ; ++j) {
            if (maze[i][j] == WALL) printf("#");
            else if (maze[i][j]==ROUTE) printf(" ");
            else if (maze[i][j]==PERSON) printf("A");
        }
        printf("\n");
    }
}

int main()
{
    srand((unsigned) time(NULL));
    initmaze();
    mazego(2,2);
    complemaze();


    //开始游戏
    char move;
    int px=2, py=1;
    maze[px][py]=PERSON;
    while(1)
    {
        printmaze();
        move = getch();
        int tempx = px ,tempy = py;
        if(move==72&&maze[px-1][py]==ROUTE){px-=1;}
        else if (move==80&&maze[px+1][py]==ROUTE){px+=1;}
        else if (move==75&&maze[px][py-1]==ROUTE){py-=1;}
        else if(move==77&&maze[px][py+1]==ROUTE){py+=1;}
        maze[px][py]=PERSON;
        if(px==finalx&&py==finaly)
        {
            printf("You make it!");
            getchar();
            break;
        }
        if(tempx!=px||tempy!=py) maze[tempx][tempy]=ROUTE;
        system("cls");
    }
    return 0;
}