#include <cstdio>
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

char filePath[100] = "D:/chhokmah/c2020/level1/p09_maze/map.in";    //地图文件的位置，运行前请修改，不知道为啥相对路径没用
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
void initConsole(); //初始化控制台
void printMap();    //绘制地图
void printPlayer(); //输出人物
void openMap();     //读取地图，人物，过关位置
void judgeWin();    //判断过关
void printWin();    //输出胜利信息
void printHelp();   //输出提示
void setPos(SHORT x,SHORT y);  //移动光标

int size_x,size_y;
char map[50][50];
int Exit[2] = {0,0};
bool gameWin = false;

enum direction{
    UP,DOWN,LEFT,RIGHT
}Dir;
struct Player{
    int x;
    int y;
    Player(int x, int y):x(x),y(y) {};

    void move(direction toward){
        int x0 = x,y0 = y;
        switch (toward){
            case UP:
                y--;break;
            case DOWN:
                y++;break;
            case LEFT:
                x--;break;
            case RIGHT:
                x++;break;
        }
        if (map[y][x] == '#') {
            x = x0;
            y = y0;
        }
    }
};



Player player(0,0);

int main(){
    initConsole();
    openMap();
    printMap();
    printPlayer();
    printHelp();
    while(!gameWin) {
        bool flag = false;
        while(!flag){
            if (_getch() == 224) {
                flag = true;
                switch (_getch()) {
                    case 72:
                        Dir = UP;
                        break;
                    case 80:
                        Dir = DOWN;
                        break;
                    case 75:
                        Dir = LEFT;
                        break;
                    case 77:
                        Dir = RIGHT;
                        break;
                }
            }
        };
        player.move(Dir);
        system("cls");
        printMap();
        printPlayer();
        printHelp();
        judgeWin();
    }
    printWin();
    system("pause");
    return 0;
}

//初始化控制台
void initConsole(){
    system("chcp 65001");   //设置代码页为UTF-8
    SetConsoleTitleA("Console_迷宫");
    CONSOLE_CURSOR_INFO pos = {1, FALSE};
    SetConsoleCursorInfo(hOut, &pos);
}

//光标位置
void setPos(SHORT x,SHORT y){
    COORD pos = {x,y};
    SetConsoleCursorPosition(hOut,pos);
}

//读取地图
void openMap(){
    memset(map,0,sizeof(map));
    FILE* fmap = fopen(filePath,"r");
    fscanf(fmap,"size:%d*%d\n",&size_x,&size_y);
    for (int i = 0; i < size_y; ++i) {
        char str[50];
        fscanf(fmap,"%s",str);
        for (int j = 0; j < size_x; ++j) {
            switch(str[j]){
                case '1':
                    map[i][j] = '#';
                    break;
                case '2':
                    player = Player(i,j);
                    break;
                case '3':
                    Exit[0] = j;Exit[1] = i;
                    break;
            }
            if (str[j] != '1')
                map[i][j] = ' ';
        }
    }
    fclose(fmap);
}

//打印地图
void printMap(){
    system("cls");
    for (int i = 0; i < size_y; ++i) {
        cout << map[i] << '\n';
    }
    setPos(Exit[0],Exit[1]);
    cout << 'O';
}

//打印玩家
void printPlayer(){
    setPos(player.x,player.y);
    cout << '@';
}

//打印帮助信息
void printHelp(){
    setPos(size_x + 3,2);
    cout << "用方向键来移动";
    setPos(size_x + 3,4);
    cout << "# —— 墙";
    setPos(size_x + 3,6);
    cout << "@ —— 你";
    setPos(size_x + 3,8);
    cout << "O —— 出口";
}

//打印
void judgeWin(){
    if (player.x ==Exit[0] && player.y == Exit[1]){
        gameWin = true;
    }
}

//打印胜利信息
void printWin(){
    setPos(size_x/2-2,size_y/2);
    cout << "你赢了！";
    setPos(0,size_y+1);
}
