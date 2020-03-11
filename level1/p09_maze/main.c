#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Game.h"

int main() {
    Start();
    char Press;
    while (IsWin())
    {
        if((Press = getch())<0) Press=getch();
        fflush(stdin);
        if(Press==87||Press==119||Press==38||Press==72)//上键
        {
            Move(0, -1);
        }
        else if(Press==68||Press==100||Press==39||Press==77)//右键
        {
            Move(1, 0);
        }
        else if(Press==83||Press==115||Press==40||Press==80)//下
        {
            Move(0, 1);
        }
        else if(Press==65||Press==97||Press==37||Press==75)//左
        {
            Move(-1, 0);
        }
    }
    system("CLS");
    printf("WIN!!");
    return 0;
}
