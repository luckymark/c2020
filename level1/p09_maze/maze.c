#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //光标设置的API
#include <time.h> 
#include <conio.h> //按键检测


//辅助宏定义
#define MAPHIGHT 15
#define MAPWIDTH 15

char ch;  //按键
//数据设计
struct{
    int x;
    int y;
}YourPosition={1,0};

int map[MAPHIGHT][MAPWIDTH]={\
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,\
0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,\
1,1,0,1,1,0,0,0,0,0,0,0,1,1,1,\
1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,\
1,0,1,1,1,1,1,1,1,1,1,0,0,1,1,\
1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,\
1,0,1,0,0,0,0,0,0,0,1,1,1,1,1,\
1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,\
1,0,1,0,1,1,0,0,0,0,0,1,1,1,1,\
1,0,1,0,0,0,0,1,1,1,0,1,1,1,1,\
1,0,1,1,1,1,1,1,1,1,0,0,1,1,1,\
1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,\
1,1,1,0,0,1,1,1,0,1,1,1,1,1,1,\
1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,\
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,\

};


void gotoxy(int x,int y);

//模块化设计
//1.画地图 ⊙ ██  可惜命令台输出不了这个符号
void drawMap(){
    for(int i=0;i<MAPHIGHT;i++){
        for(int j=0;j<MAPWIDTH;j++){
            if(map[i][j]) printf("#");
            else printf(" ");
        }printf("\n");
    }
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(handle,FOREGROUND_RED|FOREGROUND_GREEN);
    printf("\nPlease use 'w''s''a''d' to move .\n");
    printf("You are here '@' , AND '!!' is the exit .");
    gotoxy(13,14);
    printf("!!");
    
    SetConsoleTextAttribute(handle,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    gotoxy(1,0);
    printf("@");  //操作者
}
//2.按键处理
void keyDown(){
    int tempx,tempy;
    ch=getch();
    switch(ch){
        case 'w':
            tempx=YourPosition.x-1;
            tempy=YourPosition.y;
            break;
        case 's':
            tempx=YourPosition.x+1;
            tempy=YourPosition.y;
            break;
        case 'a':
            tempx=YourPosition.x;
            tempy=YourPosition.y-1;
            break;
        case 'd':
            tempx=YourPosition.x;
            tempy=YourPosition.y+1;
            break;
        default:
            printf("\a");
            return;
    }

    if(map[tempx][tempy]){
        printf("\a"); //不能向前走
        return;
    }else {
        gotoxy(YourPosition.x,YourPosition.y);
        printf(" ");
        gotoxy(tempx,tempy);
        printf("@");
    }

    YourPosition={tempx,tempy};
    return;
}
//3.结束标志
int isWin(int x,int y){
    if(x==13&&y==14){
        return 1;
    }else return 0;
}

//光标移动
void gotoxy(int x,int y){
    //调用win32 API去设置控制台的光标位置
    //找到控制台的这个窗口
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //光标的结构体
    COORD coord;
    //设置坐标
    coord.X=y; //跟想象中的矩阵不太一样
    coord.Y=x;
    //同步到控制台
    SetConsoleCursorPosition(handle,coord);
}
void HideCursor() //隐藏光标
{
	CONSOLE_CURSOR_INFO cursor;    
	cursor.bVisible = FALSE;    
	cursor.dwSize = sizeof(cursor);    
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorInfo(handle, &cursor);
}

int main(){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
    SetConsoleTextAttribute(handle,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    //system("@color 0f"); //设定的颜色会被最后一个颜色覆盖，只能设定一种颜色
    drawMap();
    HideCursor();
    while(1){
        if(_kbhit()){  //有按键操作时返回非0
            keyDown();
            if(isWin(YourPosition.x,YourPosition.y)){
                gotoxy(19,0);
                SetConsoleTextAttribute(handle,FOREGROUND_RED);
                printf(" Congratulations!!\n\n\n\n\n");
                break;
            }
        }
    }

    system("pause");
    return 0;
}