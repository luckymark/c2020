#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define MAXN 10
//need to change

#define SEED 0
static int listsize=0;
//kill magic number

int aX,aY;
//now positon
bool maze[MAXN][MAXN];

struct node{
    //std linked list
    int x;
    int y;
    //position
    struct  node* next;
};
struct node *head=NULL;
//head ptr

void insertList(int x,int y);
void createMaze();


void insertList(int x,int y){
	//insert to the head
    struct node* temp=head;
    head=(struct node*)malloc(sizeof(struct node));
    head->next=temp;
    head->x=x;
    head->y=y;
    listsize++;
}

void delList(int pos){
    if(pos>listsize){
    	//out of range
        puts("Error on delele!! No such position!!");
        exit(0);
    }
    struct node *now=head,*temp;
    if(pos==1){
    	//special
        temp=head;
        head=head->next;
        free(temp);
        listsize--;
        return;
    }
    int i;
    for(i=0;i<pos-2;++i)now=now->next;
    temp=now->next;
    now->next=temp->next;
    free(temp);
    listsize--;
}
void createMaze(char *filename){
	//prime

    if(SEED==0)srand(time(NULL));
    else srand(SEED);
    //seed

    memset(maze,0,sizeof(bool)*MAXN*MAXN);
    //set all to wall
    //0-wall 1-road

    int i;
    for (i = 0; i < MAXN; i++) {
        maze[i][0] = 1;
        maze[0][i] = 1;
        maze[MAXN - 1][i] = 1;
        maze[i][MAXN - 1] = 1;
    }
    //make the outline to be road

    insertList(2,2);
    //initialize maze's first road

    int x,y,cnt,j,r;

    while (listsize>0) {
        r = rand()%listsize+1;
        struct node* ptr=head;
        for(i=0;i<r-1;++i)ptr=ptr->next;
        x=ptr->x;
        y=ptr->y;
        delList(r);

        //判读上下左右四个方向是否为路
        cnt=0;
        for(i=x-1;i<x+2;i++){
            for(j=y-1;j<y+2;j++){
                if(abs(x-i)+abs(y-j)==1&&maze[i][j]==1){
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
                    if (abs(x-i)+abs(y-j)==1&&maze[i][j] == 0) {
                        insertList(i,j);
                    }
                }
            }
        }
    }

    maze[2][1] = 1;
    //set out

    for (i = MAXN - 3; i >= 0; i--) {
        if (maze[i][MAXN -1-2] == 1) {
        	aY=i;
        	aX=MAXN-1-1;
            maze[i][MAXN -1-1] = 1;
            break;
        }
    }
    //set in
    FILE* fp=fopen(filename,"w");
    // fprintf(fp,"%d\n",MAXN);
    for(i=0;i<MAXN;++i){
    	for(j=0;j<MAXN;++j){
            if(i==aY&&j==aX){ 
                fprintf(fp, "A");
                continue;
            }
            if(i==2&&j==1){ 
                fprintf(fp, "B");
                continue;
            }
            if(maze[i][j]==1)fprintf(fp, "O");
            else fprintf(fp,"X");
        }
        fprintf(fp,"\n");
    }
}
