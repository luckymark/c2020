#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define MAXN 15
#define MAXLEN 7

char map[MAXN][MAXN];
char buf[MAXLEN+1];

int level,best,step=0,xCounter=0;
int x,y;
//player's position

inline void welcome();
inline void printNode(int i,int j);
inline void printMap();
inline void printMark();
inline void printReadMe();
inline void moveChar(char orient);
void move(int i,int j);
inline bool checkWin();
inline void win();
inline FILE* fOpen(char *filename,char * mode);
void readMap(int _level,char *_map);
void dumpMap();

int main(){
    welcome();
    readMap(level,(char*)map);
    while(1){
        printMap();
        printMark();
        printReadMe();
        if(checkWin())win();
        char temp=getch();
        moveChar(temp);
        ++step;
    }
    return 0;
}
void readMap(int _level,char *_map){
    sprintf(buf,"%d.txt",_level);
    FILE* fp=fOpen(buf,"r");
    fscanf(fp,"%d",&best);
    fscanf(fp,"%d %d",&x,&y);
    fgetc(fp);
    int i,j;
    for(i=0;i<MAXN;++i){
        for(j=0;j<MAXN;++j){
            fscanf(fp,"%c",(_map+i*MAXN+j));
            if('X'==_map[i*MAXN+j])++xCounter;
        }
        fgetc(fp);
    }
    fclose(fp);
}
void dumpMap(){ 
	FILE* fp=fOpen(buf,"r+");
    fprintf(fp,"%05d\n",best);
    fclose(fp);
}
inline void welcome(){ 
    printf("Please enter level number:");
    scanf("%d",&level);
}
inline FILE* fOpen(char *filename,char * mode){ 
    FILE* temp=fopen(filename,mode);
    if(temp)return temp;
    else{ 
        printf("Error on %s : %s : %d , Cannot open file\n",__FILE__,__func__,__LINE__);
        exit(-1);
    }
}
inline bool checkWin(){ 
    return 0==xCounter;
}
inline void printMark(){ 
    printf("\nBest:%d\t\t\tNow:%d",best,step);
}
inline void printReadMe(){ 
    printf("\n\nNotes:\nA:Player\nB:Box\nX:Dest\n");
    puts("Using WSAD!!  And Q/q is Quit!\n");
}
inline void printNode(int i,int j){ 
    if(i==y&&j==x){
        printf("A ");
        //player
        return;
    }
    printf("%c ",map[i][j]);
}
inline void win(){ 
    if(step<best){ 
        best=step;
        dumpMap();
    }
    printf("You Win!\n");
    system("pause");
    exit(0);
}
void move(int i,int j){ 
    if(' '==map[y+i][x+j]||'X'==map[y+i][x+j]){
        //free walk
        goto update;
    }
    if((' '==map[y+2*i][x+2*j]||'X'==map[y+2*i][x+2*j])&&'B'==map[y+i][x+j]){
        map[y+i][x+j]=' ';
        if('X'==map[y+2*i][x+2*j]){
            //push box to dest
            map[y+2*i][x+2*j]='O';
            --xCounter;
        }
        else map[y+2*i][x+2*j]='B';
        goto update;
    }
    if((' '==map[y+2*i][x+2*j]||'X'==map[y+2*i][x+2*j])&&'O'==map[y+i][x+j]){
        map[y+i][x+j]='X';
        if('X'==map[y+2*i][x+2*j]){
            //push box out of dest
            map[y+2*i][x+2*j]='O';
            ++xCounter;
        }
        else map[y+2*i][x+2*j]='B';
        goto update;
    }
    return;
update:
    y+=i;
    x+=j;
}
inline void moveChar(char mode){ 
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
void printMap(){ 
    system("cls");
    int i,j;
    for(i=0;i<MAXN;++i){
        for(j=0;j<MAXN;++j){
            printNode(i,j);
        }
        puts("");
    }
}
