#include "maze.h"
#define SEED 0

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
