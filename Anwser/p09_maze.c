#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
char map[8][20]=
        {
                "***    **** **** ***",
                "****  ****   **  ***",
                "***    *****     ***",
                "***            *****",
                "*****   **  ********",
                "*****  ***   *******",
                "*********   ********",
                "*********          O"
        };
int mov_T[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int location_x,location_y;
void print()
{
    system("CLS");
    printf("press ESE to quit\n");
    int i,j;
    for(i=0;i<=7;i++)
    {
        for(j=0;j<=19;j++)
            if(i==location_x && j==location_y)  printf("T");
            else  printf("%c",map[i][j]);
        printf("\n");
    }
}
int sucess(int x,int y)
{
    if(x<0 || x>7 || y<0 || y>19)  return 0;
    if(map[x][y]=='*')  return 0;
    return 1;
}
void Gaming(int move)
{
    if(move==4)  return;
    int x=location_x+mov_T[move][0];
    int y=location_y+mov_T[move][1];
    if(sucess(x,y))
    {
        location_x=x;
        location_y=y;
        print();
    }
}
int main()
{

    location_x=0;
    location_y=3;
    print();
    int move_press;
    int move;
    while( (move_press=getch())!=0x1B )
    {
        switch(move_press)
        {
            case 0xE0:
                switch (move_press=getch())
                {
                    case 72:
                        move=0;break;
                    case 80:
                        move=1;break;
                    case 75:
                        move=2;break;
                    case 77:
                        move=3;break;
                    default:
                        move=0;break;
                }
                break;
            default:
                move=4;
                break;
        }
        Gaming(move);
        if(location_y==19 && location_x==7)
        {
            system("CLS");
            printf("You Win!");
            break;
        }
    }
    return 0;
}
