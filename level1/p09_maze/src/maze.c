#include"maze.h"

bool maze[MAXN][MAXN];
int aJ,aI;

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
