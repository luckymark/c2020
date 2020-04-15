#include"boxmap.h"
static void welcome();
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
inline void welcome(){ 
    printf("Please enter level number:");
    scanf("%d",&level);
}
