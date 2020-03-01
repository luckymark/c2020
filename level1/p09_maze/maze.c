#include"maze.h"
int i;
int main(){
    int temp,j;
    createMaze();
    while(1){
        system("cls");
        //flush frame
        for(i=0;i<MAXN;++i){
            for(j=0;j<MAXN;++j){
                if(maze[i][j]){
                    printf("%c ",3);
                    //baffle
                }
                else if(i==aY&&j==aX)printf("A ");
                    //aYou are Here
                else if(i==2&&j==1)printf("B ");
                    //Destination
                else printf("  ");
                //road
            }
            printf("\n");
        }
        puts("\n!!Using WSAD to get B!!\n");
        //instruction
        if(aX==1&&aY==2){
            goto end;
            //win
        }
        temp=getch();

        switch(temp){

            case 'w':
                if((aY>1)&&(maze[aY-1][aX]!=1)){
                    aY-=1;
                }
                break;

            case 's':
                if(((aY<MAXN-2)&&(maze[aY+1][aX]!=1)))
                {
                    aY+=1;
                }
                break;

            case 'a':
                if((aX>1)&&maze[aY][aX-1]!=1){
                    aX-=1;
                }
                break;

            case 'd':
                if((aX<MAXN-2)&&maze[aY][aX+1]!=1){
                    aX+=1;
                }
                break;
            case 'q':
            	puts("Quit~");
            	exit(0);
        }
    }
    end:
    printf("\n\nYou Win!!!\nInput any to Quit\n");
    getch();
    return 0;
}

