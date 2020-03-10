#include <conio.h>
#include <windows.h>

#include <cstdio>
#include <iostream>
#define MAXN 10     //最大箱子个数
#define MAXLEVEL 3  //关卡数量，要增加请修改
using namespace std;

enum direction { UP, DOWN, LEFT, RIGHT } Dir;
struct Player;

char filePath[100] = ".";  //地图文件所在的文件夹，“.”代表当前文件夹
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
void initConsole();                             //初始化控制台
void printMap();                                //绘制地图和箱子
bool canMove(int x, int y, direction front);    //移动箱子
void printPlayer();                             //输出人物
void subMove(int& x, int& y, direction front);  //辅助函数
void movePlayer(Player& player, direction front);
void openMap();                 //读取地图，人物，过关位置
void judgeWin();                //判断过关
void printWin();                //输出胜利信息
void printHelp();               //输出提示
void setPos(SHORT x, SHORT y);  //移动光标
void printExit();               //输出箱子要移动的位置

int moveTimes = 0;
int levelNum = 1;
int boxNumber = 0;
int size_x, size_y;
char map[50][50];
int Exit[MAXN][2] = {0};
bool gameWin = false;
bool isContinue = true;

//人物
struct Player {
    int x;
    int y;
    Player(int x = 0, int y = 0) : x(x), y(y){};
};

Player player(0, 0);

int main() {
    char scorePath[100];
    strcpy(scorePath, filePath);
    strcat(scorePath, "/score.txt");
    FILE* score = fopen(scorePath, "a+");
    initConsole();
    while (isContinue) {
        bool restart = false;
        openMap();
        printMap();
        printExit();
        printPlayer();
        printHelp();
        while (!gameWin) {
            bool flag = false;
            while (!flag) {
                unsigned char ch = _getch();
                if (ch == 224) {
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
                } else if (ch == 'r' || ch == 'R') {
                    flag = true;
                    restart = true;
                }
            }
            system("cls");
            if (restart) break;
            movePlayer(player, Dir);
            printMap();
            printExit();
            printPlayer();
            printHelp();
            judgeWin();
        }
        if (gameWin) {
            fprintf(score, "level %2d:%4d 步\n", levelNum, moveTimes);
            printWin();
        }
    }
    fprintf(score, "----------------\n");
    fclose(score);
    setPos(0, size_y + 1);
    system("pause");
    return 0;
}

//初始化控制台
void initConsole() {
    system("chcp 65001");  //设置代码页为UTF-8
    SetConsoleTitleA("Console_推箱子");
    CONSOLE_CURSOR_INFO pos = {1, FALSE};
    SetConsoleCursorInfo(hOut, &pos);
}

void move(int& x, int& y, direction front) {}

//光标位置
void setPos(SHORT x, SHORT y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(hOut, pos);
}

//读取地图
void openMap() {
    moveTimes = 0;
    boxNumber = 0;
    gameWin = false;
    memset(Exit, 0, sizeof(Exit));
    memset(map, 0, sizeof(map));
    char mapPath[100] = {0};
    char mapLevel[20];
    sprintf(mapLevel, "/map%d.in", levelNum);
    strcpy(mapPath, filePath);
    strcat(mapPath, mapLevel);
    FILE* fmap = fopen(mapPath, "r");
    fscanf(fmap, "size:%d*%d\n", &size_x, &size_y);
    for (int i = 0; i < size_y; ++i) {
        char str[50];
        fscanf(fmap, "%s", str);
        for (int j = 0; j < size_x; ++j) {
            switch (str[j]) {
                case '0':
                    map[i][j] = ' ';
                    break;
                case '1':  //墙
                    map[i][j] = '#';
                    break;
                case '2':  //玩家的位置
                    map[i][j] = ' ';
                    player = Player(j, i);
                    break;
                case '3':  //箱子要移到的位置
                    map[i][j] = ' ';
                    Exit[boxNumber][0] = j;
                    Exit[boxNumber][1] = i;
                    boxNumber++;
                    break;
                case '4':  //箱子的位置
                    map[i][j] = 'O';
                    break;
            }
        }
        map[i][size_x] = '\0';
    }
    fclose(fmap);
}

//打印地图
void printMap() {
    system("cls");
    for (int i = 0; i < size_y; ++i) {
        cout << map[i] << '\n';
    }
}

//打印玩家
void printPlayer() {
    setPos(player.x, player.y);
    cout << '@';
}

//打印帮助信息
void printHelp() {
    setPos(size_x + 3, 2);
    cout << "用方向键来移动";
    setPos(size_x + 3, 4);
    cout << "# —— 墙";
    setPos(size_x + 3, 6);
    cout << "@ —— 你";
    setPos(size_x + 3, 8);
    cout << "O —— 箱子";
    setPos(size_x + 3, 10);
    cout << "X —— 箱子要移到的位置";
    setPos(size_x + 3, 12);
    cout << "r,R —— 重新开始当前游戏";
    setPos(size_x + 3, 14);
    cout << "当前移动了 " << moveTimes << " 次";
}

void judgeWin() {
    gameWin = true;
    for (int i = 0; i < boxNumber; ++i) {
        int x = Exit[i][0], y = Exit[i][1];
        if (map[y][x] != 'O') {
            gameWin = false;
        }
    }
}

//打印胜利信息
void printWin() {
    setPos(size_x / 2 - 2, size_y / 2 - 1);
    cout << "你赢了！";
    if (levelNum < MAXLEVEL) {
        setPos(size_x / 2 - 4, size_y / 2);
        cout << "是否继续？";
        setPos(size_x / 2 - 2, size_y / 2 + 1);
        cout << "Y/N";
        bool flag = false;
        while (!flag) {
            unsigned char ch = _getch();
            if (ch == 'Y' || ch == 'y') {
                flag = true;
                levelNum++;
            } else if (ch == 'N' || ch == 'n') {
                flag = true;
                isContinue = false;
            }
        }
    } else {
        isContinue = false;
    }
}

void subMove(int& x, int& y, direction front) {
    switch (front) {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
    }
}

//移动箱子
bool canMove(int x, int y, direction front) {
    int x0 = x, y0 = y;
    subMove(x, y, front);
    if (map[y][x] == '#' || map[y][x] == 'O') {
        return false;
    } else {
        map[y][x] = 'O';
        map[y0][x0] = ' ';
        return true;
    }
}
void movePlayer(Player& player, direction front) {
    int x0 = player.x, y0 = player.y;
    subMove(player.x, player.y, front);
    if (map[player.y][player.x] == '#') {
        player.x = x0;
        player.y = y0;
    } else if (map[player.y][player.x] == 'O') {
        if (!canMove(player.x, player.y, Dir)) {
            player.x = x0;
            player.y = y0;
        }
    }
    if (player.x != x0 || player.y != y0) {
        moveTimes++;
    }
}

void printExit() {
    for (int i = 0; i < boxNumber; ++i) {
        int x = Exit[i][0], y = Exit[i][1];
        setPos(x, y);
        if (map[y][x] == ' ') {
            cout << 'X';
        }
    }
}
