#ifndef MAZE_H
#define MAZE_H

#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include"list.h"

#define MAXN 20
#define BI 2
#define BJ 1
#define ROAD 1
#define WALL 0
//destination's positon



extern bool maze[MAXN][MAXN];
extern int aJ,aI;
//player's positon

void createMaze();
void printMaze();
void moveChar(char mode);

static  inline bool isWin();
static  inline void win();
static  inline void move(int i,int j);
static  inline void moveQ();
static  inline void moveDefault();
static  inline void initSeed(int _seed);
static  inline void setOutlet();
static  inline void setEntrance();
static  inline void setOutlineRoad();
static  inline bool isConvertable(int x,int y);
static  inline void addNeighbors(int x,int y);
static  inline void printNode(int i,int j);
static  inline bool isValid(int i,int j);


inline void win(){ 
    printMaze();
    printf("\n\nYou Win!!!\nInput any to Quit\n");
    getch();
    exit(0);
}
inline bool isWin(){ 
    return BJ==aJ&&BI==aI;
}
inline void move(int i,int j){ 
    if(isValid(aI+i,aJ+j)&&ROAD==maze[aI+i][aJ+j]){
        aI+=i;
        aJ+=j;
    }
}
inline void moveQ(){ 
    puts("Quit~");
    exit(0);
}
inline void moveDefault(){ 
    puts("Unknown Input!");
    getch();
}
inline void initSeed(int _seed){ 
    if(0==_seed)srand(time(NULL));
    else srand(_seed);
}
inline void setOutlet(){ 
    maze[2][1] = ROAD;
}
inline void setEntrance(){ 
    int i;
    for(i=MAXN-3;i>=0;i--) {
        if (ROAD==maze[i][MAXN-1-2]) {
            aI=i;
            aJ=MAXN-1-1;
            maze[i][MAXN-1-1]=ROAD;
            break;
        }
    }
}
inline void setOutlineRoad(){ 
    int i;
    for(i=0;i<MAXN;++i) {
        maze[i][MAXN-1]=maze[MAXN-1][i]=maze[0][i]=maze[i][0]=ROAD;
    }
}
inline bool isConvertable(int x,int y){ 
    //判读上下左右四个方向是否为路
    int i,j,cnt=0;
    for(i=x-1;i<x+2;i++){
        for(j=y-1;j<y+2;j++){
            if(1==abs(x-i)+abs(y-j)&&ROAD==maze[i][j]){
                ++cnt;
            }
        }
    }
    if(cnt<=1)return true;
    else return false;
}
inline void addNeighbors(int x,int y){ 
    int i,j;
    for(i=x-1;i<x+2;i++){
        for(j=y-1;j<y+2;j++){
            if(1==abs(x-i)+abs(y-j)&&WALL==maze[i][j]){
                insertList(i,j);
            }
        }
    }
}
inline void printNode(int i,int j){ 
    if(WALL==maze[i][j]){
        printf("%c ",3);
        //baffle : somewhat weird char
    }
    else if(i==aI&&j==aJ)printf("A ");
    //You are Here
    else if(BI==i&&BJ==j)printf("B ");
    //Destination
    else printf("  ");
    //road
}
inline bool isValid(int i,int j){ 
    return (i<MAXN-1)&&(i>0)&&(j<MAXN-1)&&(j>0);
}

#endif
