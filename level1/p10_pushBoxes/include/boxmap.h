#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define MAXN 15
#define MAXLEN 7

extern char map[MAXN][MAXN];
extern char buf[MAXLEN+1];

extern int level,best,step,xCounter;
extern int x,y;
//player's position

void printNode(int i,int j);
void printMap();
void printMark();
void printReadMe();
void moveChar(char orient);
void move(int i,int j);
bool checkWin();
void win();
FILE* fOpen(char *filename,char * mode);
void readMap(int _level,char *_map);
void dumpMap();

static inline FILE* fOpen(char *filename,char * mode){ 
    FILE* temp=fopen(filename,mode);
    if(temp)return temp;
    else{ 
        printf("Error on %s : %s : %d , Cannot open file\n",__FILE__,__func__,__LINE__);
        exit(-1);
    }
}
static inline bool checkWin(){ 
    return 0==xCounter;
}
static inline void printMark(){ 
    printf("\nBest:%d\t\t\tNow:%d",best,step);
}
static inline void printReadMe(){ 
    printf("\n\nNotes:\nA:Player\nB:Box\nX:Dest\n");
    puts("Using WSAD!!  And Q/q is Quit!\n");
}
static inline void printNode(int i,int j){ 
    if(i==y&&j==x){
        printf("A ");
        //player
        return;
    }
    printf("%c ",map[i][j]);
}
static inline void win(){ 
    if(step<best){ 
        best=step;
        dumpMap();
    }
    printf("You Win!\n");
    system("pause");
    exit(0);
}
static inline void moveChar(char mode){ 
    mode=tolower(mode);
    switch(mode){
        case 'w':
            move(-1,0);
            break;
        case 's':
            move(1,0);
            break;
        case 'a':
            move(0,-1);
            break;
        case 'd':
            move(0,1);
            break;
        case 'q':
            printf("\nQuited");
            exit(0);
        default:
            printf("\nUnkstepn Input\n");
            getch();
    }
}
