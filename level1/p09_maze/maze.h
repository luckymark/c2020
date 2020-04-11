#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"list.h"

#define MAXN 20
#define SEED 0
#define BI 2
#define BJ 1
#define ROAD 1
#define WALL 0
//destination's positon



bool maze[MAXN][MAXN];
int aJ,aI;
//player's positon

void createMaze();
void printMaze();
void moveChar(char mode);
inline bool isWin();
inline void win();
inline void move(int i,int j);
inline void moveQ();
inline void moveDefault();
inline void initSeed(int _seed);
inline void setOutlet();
inline void setEntrance();
inline void setOutlineRoad();
inline bool isConvertable(int x,int y);
inline void addNeighbors(int x,int y);
inline void printNode(int i,int j);
inline bool isValid(int i,int j);


void createMaze(){
    //prime algorithm
    //具体我也不懂，就是好像这个算法的思想就是最小生成树
    //导致了每两个可行点之间有且仅有一条路径

    setOutlineRoad();
    insertList(2,2);
    //list是墙的collective，这个list中的墙在一定条件下为变化为路
    //(2,2)满足变化为路的条件

    int x,y,r;
    while (getListSize()>0) {

        r = rand()%getListSize()+1;
        struct node* ptr=NULL;
        ptr=getElement(r);
        x=ptr->x;
        y=ptr->y;
        delList(r);

        if (isConvertable(x,y)) {
            maze[x][y]=ROAD;
            //change wall into road
            addNeighbors(x,y);
            //add new walls to list
        }
    }
    setOutlet();
    setEntrance();
}
void printMaze(){ 
    system("cls");
    //flush

    int i,j;
    for(i=0;i<MAXN;++i){
        for(j=0;j<MAXN;++j){
            printNode(i,j);
        }
        printf("\n");
    }
    puts("\n!!Using WSAD to get B!!\n");
}
void moveChar(char mode){ 
    mode=toupper(mode);
    switch(mode){
        case 'W':
            move(-1,0);
            break;
        case 'S':
            move(1,0);
            break;
        case 'A':
            move(0,-1);
            break;
        case 'D':
            move(0,1);
            break;
        case 'Q':
            moveQ();
            break;
        default:
            moveDefault();
    }
}
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
