#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<conio.h>
#define MAXN 15
bool maze[MAXN][MAXN];
int i;
int main(){ 
    for(i=0;i<MAXN;++i){ 
        maze[0][i]=1;
    }
    for(i=0;i<MAXN;++i){ 
        maze[i][0]=1;
    }
    for(i=0;i<MAXN;++i){ 
        maze[i][14]=1;
    }
    for(i=0;i<MAXN;++i){ 
        maze[14][i]=1;
    }
    for(i=0;i<10;++i)maze[3][i]=1;
    for(i=3;i<6;++i)maze[i][9]=1;
    maze[5][10]=maze[5][11]=1;
    for(i=0;i<7;++i)maze[7][i]=maze[7][8+i]=1;
    for(i=8;i<11;++i)maze[i][6]=1;
    for(i=7;i<12;++i)maze[10][i]=1; 
    for(i=10;i>8;--i)maze[i][11]=1;
    maze[14][7]=0;
    maze[0][7]=0;
    //make baffle

    int x=7,y=14;
    //Your Position

    int temp,j;
    while(1){ 
        system("cls");
    	//flush frame
        for(i=0;i<MAXN;++i){ 
            for(j=0;j<MAXN;++j){
                if(maze[i][j]){ 
                    printf("*");
                    //baffle
                } 
                else if(i==y&&j==x)printf("A");
                //You are Here
                else if(i==0&&j==7)printf("B");
                //Destination
                else printf(" ");
                //road
            }
            printf("\n");
        } 
        puts("\n!!Using WSAD to get B!!\n");
        //instruction
        if(x==7&&y==0){
        	goto end;
        	//win
		}
        temp=getch();
        
        switch(temp){ 

         case 'w':
             if((y>0)&&(maze[y-1][x]!=1)){ 
                y-=1;
             }
             break;

         case 's':
             if(((y<14)&&(maze[y+1][x]!=1)))
             { 
                y+=1;
             }
             break;

         case 'a':
             if((x>0)&&maze[y][x-1]!=1){ 
                x-=1;
             }
             break;

         case 'd':
             if((x<14)&&maze[y][x+1]!=1){ 
                x+=1;
             }
             break;
        }
    }
end:
	printf("\n\nYou Win\nInput any to Quit\n");
	getch();
    return 0;
}

