#include"maze.h"
int main(){
    initSeed(SEED);
    createMaze();
     
    register char temp;
    while(1){
        printMaze();
        temp=getch();
        moveChar(temp);
        if(isWin())win();
    }
}
