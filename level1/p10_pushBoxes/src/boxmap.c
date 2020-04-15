#include"boxmap.h"
char map[MAXN][MAXN];
char buf[MAXLEN+1];

int level,best,step=0,xCounter=0;
int x,y;

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
