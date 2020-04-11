#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"list.h"

#define MAXN 20
#define SEED 0


bool maze[MAXN][MAXN];
//0-wall 1-road
int aX,aY;
//player's positon

void createMaze();
void printMaze();
void move(char mode);
inline bool isWin();
inline void win();
inline void moveA();
inline void moveD();
inline void moveS();
inline void moveW();
inline void moveQ();
inline void moveDefault();
inline void initSeed(int _seed);
inline void repair();


void createMaze(){
    //prime algorithm
    int i;
    for(i=0;i<MAXN;++i) {
        maze[i][MAXN-1]=maze[MAXN-1][i]=maze[0][i]=maze[i][0]=1;
    }
    //make the outline to be road

    insertList(2,2);
    //initialize maze's first road

    int x,y,cnt,j,r;
    while (getListSize()>0) {
        r = rand()%getListSize()+1;
        struct node* ptr=head;
        for(i=0;i<r-1;++i)ptr=ptr->next;
        x=ptr->x;
        y=ptr->y;
        delList(r);

        //判读上下左右四个方向是否为路
        cnt=0;
        for(i=x-1;i<x+2;i++){
            for(j=y-1;j<y+2;j++){
                if(1==abs(x-i)+abs(y-j)&&1==maze[i][j]){
                    ++cnt;
                }
            }
        }
        if (cnt <= 1) {
            maze[x][y] = 1;
            //change into road

            //add new walls to list
            for (i=x-1;i<x+2;i++) {
                for (j=y-1;j<y+2;j++) {
                    if (1==abs(x-i)+abs(y-j)&& 0==maze[i][j] ) {
                        insertList(i,j);
                    }
                }
            }
        }
    }

    maze[2][1] = 1;
    //set outlet

    for (i = MAXN - 3; i >= 0; i--) {
        if (1==maze[i][MAXN -1-2]) {
            aY=i;
            aX=MAXN-1-1;
            maze[i][MAXN-1-1] = 1;
            break;
        }
    }
    //set entrance

    for(i=0;i<MAXN;++i){
        for(j=0;j<MAXN;++j){
            maze[i][j]^=1;
        }
    }
    //solve confliction with the next part
}
void printMaze(){ 
    system("cls");
    //flush

    int i,j;
    for(i=0;i<MAXN;++i){
        for(j=0;j<MAXN;++j){
            if(maze[i][j]){
                printf("%c ",3);
                //baffle : somewhat weird char
            }
            else if(i==aY&&j==aX)printf("A ");
            //You are Here
            else if(2==i&&1==j)printf("B ");
            //Destination
            else printf("  ");
            //road
        }
        printf("\n");
    }
    puts("\n!!Using WSAD to get B!!\n");
}
void move(char mode){ 
    switch(mode){
        case 'W':
        case 'w':
            moveW();
            break;
        case 'S':
        case 's':
            moveS();
            break;
        case 'A':
        case 'a':
            moveA();
            break;
        case 'D':
        case 'd':
            moveD();
            break;
        case 'Q':
        case 'q':
            moveQ();
            break;
        default:
            moveDefault();
    }
}
inline void win(){ 
    printf("\n\nYou Win!!!\nInput any to Quit\n");
    getch();
    exit(0);
}
inline bool isWin(){ 
    return 1==aX&&2==aY;
}
inline void moveA(){ 
    if((aX>1)&&maze[aY][aX-1]!=1){
        aX-=1;
    }

}
inline void moveD(){ 
    if((aX<MAXN-2)&&maze[aY][aX+1]!=1){
        aX+=1;
    }
}
inline void moveW(){ 
    if((aY>1)&&(maze[aY-1][aX]!=1)){
        aY-=1;
    }
}
inline void moveS(){ 
    if(((aY<MAXN-2)&&(maze[aY+1][aX]!=1)))
    {
        aY+=1;
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
