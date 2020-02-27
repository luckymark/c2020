#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<stdbool.h>

#define MAXN 15
#define MAXLEN 7

char map[MAXN][MAXN];
char buf[MAXLEN+1];
//store filename
int level,best,now=0;
int x,y;
//your position
bool win=false;
//win-flag variable
int i,j;
//temp
char temp;
//temp

void readMap();
void dumpMap();
int main(){
    printf("Please enter level number:");
    scanf("%d",&level);
    readMap();
    while(1){
        system("cls");
        //flush frame
        for(i=0;i<MAXN;++i){
            for(j=0;j<MAXN;++j){
                if(i==y&&j==x){
                    printf("A ");
                    //You are  Here
                    continue;
                }
                printf("%c ",map[i][j]);
                //painting map
            }
            puts("");
        }
        printf("\nBest:%d\t\t\tNow:%d",best,now);
        //Mark Board
        printf("\n\nNotes:\nA:Player\nB:Box\nX:Dest\n");
        puts("Using WSAD!!  And q is Quit!\n");
        //instructions
        
        if(win){
        	//have win
            if(now<best){ 
                best=now;
                dumpMap();
            }
            printf("You Win\n");
            system("pause");
            exit(0);
        }

        temp=getch();
        switch(temp){
            case 'w':
                if(map[y-1][x]==' '||map[y-1][x]=='X'){
                	//walk free
                    y-=1;
                    break;
                }
                if((map[y-2][x]==' '||map[y-2][x]=='X')&&map[y-1][x]=='B'){
                	//push box into dest
                    map[y-1][x]=' ';
                    if(map[y-2][x]=='X'){
                        map[y-2][x]='O';
                    }
                    else map[y-2][x]='B';
                    y-=1;
                    break;
                }
                if((map[y-2][x]==' '||map[y-2][x]=='X')&&map[y-1][x]=='O'){
                	//push box out of dest
                    map[y-1][x]='X';
                    if(map[y-2][x]=='X'){
                        map[y-2][x]='O';
                    }
                    else map[y-2][x]='B';
                    y-=1;
                    break;
                }
                break;
            case 's':
                if(map[y+1][x]==' '||map[y+1][x]=='X')
                {
                    y+=1;
                    break;
                }
                if((map[y+2][x]==' '||map[y+2][x]=='X')&&map[y+1][x]=='B'){
                    map[y+1][x]=' ';
                    if(map[y+2][x]=='X'){
                        map[y+2][x]='O';
                    }
                    else map[y+2][x]='B';
                    y+=1;
                    break;
                }
                if((map[y+2][x]==' '||map[y+2][x]=='X')&&map[y+1][x]=='O'){
                    map[y+1][x]='X';
                    if(map[y+2][x]=='X'){
                        map[y+2][x]='O';
                    }
                    else map[y+2][x]='B';
                    y+=1;
                    break;
                }
                break;
            case 'a':
                if(map[y][x-1]==' '||map[y][x-1]=='X'){
                    x-=1;
                    break;
                }
                if((map[y][x-2]==' '||map[y][x-2]=='X')&&map[y][x-1]=='B'){
                    map[y][x-1]=' ';
                    if(map[y][x-2]=='X'){
                        map[y][x-2]='O';
                    }
                    else map[y][x-2]='B';

                    x-=1;
                    break;
                }
                if((map[y][x-2]==' '||map[y][x-2]=='X')&&map[y][x-1]=='O'){
                    map[y][x-1]='X';
                    if(map[y][x-2]=='X'){
                        map[y][x-2]='O';
                    }
                    else map[y][x-2]='B';

                    x-=1;
                    break;
                }
                break;
            case 'd':
                if(map[y][x+1]==' '||map[y][x+1]=='X'){
                    x+=1;
                    break;
                }
                if((map[y][x+2]==' '||map[y][x+2]=='X')&&map[y][x+1]=='B'){
                    map[y][x+1]=' ';
                    if(map[y][x+2]=='X'){
                        map[y][x+2]='O';
                    }
                    else map[y][x+2]='B';
                    x+=1;
                    break;
                }
                if((map[y][x+2]==' '||map[y][x+2]=='X')&&map[y][x+1]=='O'){
                    map[y][x+1]='X';
                    if(map[y][x+2]=='X'){
                        map[y][x+2]='O';
                    }
                    else map[y][x+2]='B';
                    x+=1;
                    break;
                }
                break;
            case 'q':
            	printf("\nQuited");
            	exit(0);
        }
        now++;
        //renew mark
        win=true;
        for(i=1;i<MAXN-1;++i){
            for(j=1;j<MAXN-1;++j){
                if(map[i][j]=='X')
                    win=false;
            }

        }
        //check if have win
    }
    return 0;
}
void readMap(){
    sprintf(buf,"%d.txt",level);
    FILE* fp=fopen(buf,"r");
    fscanf(fp,"%d",&best);
    //Best Mark
    fscanf(fp,"%d %d",&x,&y);
    //initialize Your Position
    fgetc(fp);
    for(i=0;i<MAXN;++i){
        for(j=0;j<MAXN;++j){
            fscanf(fp,"%c",&map[i][j]);
        }
        fgetc(fp);
    }
    fclose(fp);
}
void dumpMap(){ 
	FILE* fp=fopen(buf,"r");
    fscanf(fp,"%d",&now);
    fscanf(fp,"%d %d",&x,&y);
    fgetc(fp);
    for(i=0;i<MAXN;++i){
        for(j=0;j<MAXN;++j){
            fscanf(fp,"%c",&map[i][j]);
        }
        fgetc(fp);
    }
    fclose(fp);
    
    fp=fopen(buf,"w");
    fprintf(fp,"%d\n",best);
    fprintf(fp,"%d %d\n",x,y);
    for(i=0;i<MAXN;++i){
        for(j=0;j<MAXN;++j){
            fprintf(fp,"%c",map[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}
