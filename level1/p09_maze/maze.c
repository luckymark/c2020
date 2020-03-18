#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#define WIDTH 22
#define LENGTH 22


int getch(void)
{
    struct termios tm, tm_old;
    int fd = 0, ch;

    if (tcgetattr(fd, &tm) < 0) {//保存现在的终端设置
        return -1;
    }

    tm_old = tm;
    cfmakeraw(&tm);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
    if (tcsetattr(fd, TCSANOW, &tm) < 0) {//设置上更改之后的设置
        return -1;
    }

    ch = getchar();
    if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//更改设置为最初的样子
        return -1;
    }

    return ch;
}

void printMaze(int* maze)  //打印地图
{
    system("clear");
    int i,j;
    printf("maze-sk\n使用方向键操控♂,出口为♀\n");
    for(i=0;i<LENGTH;i++)
    {
        for(j=0;j<WIDTH;j++){
            switch(*(maze+i*WIDTH+j)){
                case 0: printf("■");break;     //墙
                case 1: printf("  ");break;     //路
                case 2: printf("♂");break;     //人
                case 3: printf("♀");break;     //出口
                case 4: printf("△");break;     //成功
            }
        }
        printf("\n");}
}

void swap(int* x,int* y)   //交换两个数
{
    int t=*x;
    *x = *y;
    *y = t;
}

void Move(int* x,int* y,int* maze)       //通过交换两个数,实现人物的移动
{
    int Dire=getch();
    switch(Dire){
        case 72: if(*(maze+(*x-1)*WIDTH+*y)) {swap(maze+(*x-1)*WIDTH+*y,maze+*x*WIDTH+*y); (*x)--;}
            break;
        case 80: if(*(maze+(*x+1)*WIDTH+*y)) {swap(maze+(*x+1)*WIDTH+*y,maze+*x*WIDTH+*y); (*x)++;}
            break;
        case 77: if(*(maze+*x*WIDTH+*y+1))   {swap(maze+*x*WIDTH+*y+1,maze+*x*WIDTH+*y); (*y)++;}
            break;
        case 75: if(*y-1>=0 && *(maze+*x*WIDTH+*y-1)) {swap(maze+*x*WIDTH+*y-1,maze+*x*WIDTH+*y); (*y)--;}
            break;

    }
}

int main() {
    int maze[LENGTH][WIDTH]=
            {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
             {0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,0},
             {0,1,0,0,0,0,0,1,0,1,1,0,0,0,1,0,0,0,0,0,1,0},
             {0,1,0,1,0,1,1,1,0,0,1,0,1,0,1,1,1,1,1,1,1,0},
             {0,1,0,1,0,0,0,1,1,0,1,0,1,0,0,0,0,0,1,0,0,0},
             {0,1,0,1,0,1,0,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0},
             {0,1,0,1,1,1,1,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0},
             {0,1,0,0,0,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0},
             {0,1,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,0,0,0,0},
             {0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,1,1,0,1,0},
             {0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,0},
             {0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,0},
             {0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0},
             {0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,0},
             {0,1,1,1,0,1,1,1,1,0,1,1,1,0,1,0,0,0,1,0,1,0},
             {0,1,0,1,0,0,0,0,1,0,0,0,1,1,1,1,1,0,1,0,1,0},
             {0,1,0,1,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,0,1,0},
             {0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0},
             {0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0},
             {0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0},
             {2,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
            };//地图数组
    int x= 20,y=0 ;
    printMaze((int*)maze);
    while (1) {
        Move(&x,&y,(int*)maze);
        if (maze[0][20]!=3) {
            maze[1][20]=1;
            maze[0][20]=4;}    //弱鸡地"优化"最后一步显示效果
        printMaze((int*)maze);
        if(maze[0][20] != 3 )            //不知道为什么放在while里面会有问题
            break;
    }
    printf("恭喜你成功走出了迷宫\n");
    printf("按任意键退出\n");
    getch();
    return 0;
}