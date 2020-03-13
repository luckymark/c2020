#include <windows.h>

#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cstring>

#define CHANGE 1     //每次变异改变的基因数量
#define MAXN 50      //地图大小
#define TIMES 1000   //迭代次数
#define GENE 100     //基因长度(移动步数）
#define NUMBER 5000  //每代个体数量
#define FATHER 50    //父代数量
#define REWARD 5000  //到达终点的适应度
using namespace std;

const char filePath[100] = "./map.in";
bool map[MAXN][MAXN];
bool visited[MAXN][MAXN];
int row, column;
int xExit, yExit;
int times = 0;  //到达终点要用的次数
int age = 0;
int minTimes = GENE;

typedef struct Player {
    int x;
    int y;
    int adapt;
    int times;
    int gene[GENE];
} Player;
Player player[NUMBER], tempPlayer[FATHER];

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
void readMap();                                //读取地图
void born();                                   //创造第一世代
int move(Player& player, int dir);             //移动
Player cross(Player playerA, Player playerB);  //交叉变异
void playerAdapt(Player& player);              //适应度
bool cmp(const Player& A, const Player& B);    //比较函数
void createNext();                             //制造下一代
//播放当前最佳个体
void setPos(SHORT x, SHORT y);  //移动光标
void initConsole();             //初始化控制台
void printMap();                //绘制地图
void printPlayer(Player play);  //绘制玩家游玩过程

int main() {
    initConsole();
    Player bestPlayer;
    readMap();
    born();
    while (!times) {
        srand((unsigned)time(nullptr));
        for (age = 0; age < TIMES; ++age) {
            for (int j = 0; j < NUMBER; ++j) {
                playerAdapt(player[j]);
            }
            sort(player, player + NUMBER, cmp);
            bestPlayer = player[0];
            createNext();
        }
        printPlayer(bestPlayer);
    }
    setPos(1, row + 1);
    printf("The minimum number of steps is less than or equal to %d\n",
           bestPlayer.times);
    printf("gene:");
    for (int i = 0; i < times; ++i) {
        printf("%d", bestPlayer.gene[i]);
    }
    printf("\n");
    system("pause");
}

bool cmp(const Player& A, const Player& B) { return A.adapt > B.adapt; }

void readMap() {
    FILE* file = fopen(filePath, "r");
    fscanf(file, "size:%d*%d", &column, &row);
    for (int i = 0; i < row; ++i) {
        char str[MAXN];
        fscanf(file, "%s", str);
        for (int j = 0; j < column; ++j) {
            if (str[j] == '1') {
                map[i][j] = 1;
            } else {
                map[i][j] = 0;
            }
            if (str[j] == '3') {
                xExit = i;
                yExit = j;
            }
        }
    }
}

void born() {
    for (int i = 0; i < NUMBER; ++i) {
        player[i].x = 1;
        player[i].y = 1;
        for (int j = 0; j < GENE; ++j) {
            player[i].gene[j] = rand() % 4;
        }
    }
}

Player cross(Player playerA, Player playerB) {
    int p = rand() % (times ? times : GENE);
    Player son;
    son.x = 1;
    son.y = 1;
    son.adapt = 0;
    son.times = 0;
    for (int i = 0; i < p; ++i) {
        son.gene[i] = playerA.gene[i];
    }
    for (int i = p; i < GENE; ++i) {
        son.gene[i] = playerB.gene[i];
    }
    for (int i = 0; i < CHANGE; ++i) {
        int r = rand() % (times ? times : GENE);
        son.gene[r] = rand() % 4;
    }
    return son;
}

int move(Player& player, int dir) {
    int flag;
    int x0 = player.x, y0 = player.y;
    switch (dir) {
        case 0:
            x0--;
            break;
        case 1:
            x0++;
            break;
        case 2:
            y0--;
            break;
        case 3:
            y0++;
            break;
    }
    if (map[x0][y0] == 1) {
        flag = -1;  //撞墙
    } else if (visited[x0][y0]) {
        player.x = x0;
        player.y = y0;
        flag = -5;  //走回头路
    } else {
        player.times++;
        visited[x0][y0] = true;
        player.x = x0;
        player.y = y0;
        flag = 0;  //正确走路
    }
    if (player.x == xExit && player.y == yExit) {
        flag = REWARD;
    }
    return flag;
}

void playerAdapt(Player& play) {
    memset(visited, 0, sizeof(visited));
    int sum = 0;
    int num = times ? times : GENE;
    for (int i = 0; i < num; ++i) {
        sum += move(play, play.gene[i]);
        if (play.x == xExit && play.y == yExit) {
            printPlayer(play);
            //测试
            //            play.x = 1;
            //            play.y = 1;
            //            playerAdapt(play);
            times = i;
            break;
        }
    }
    sum -= (abs(play.x - xExit) + abs(play.y - yExit));
    play.adapt = sum;
}

void createNext() {
    for (int i = 0; i < FATHER; ++i) {
        player[i].x = 1;
        player[i].y = 1;
        player[i].adapt = 0;
        player[i].times = 0;
    }
    for (int i = FATHER; i < NUMBER; ++i) {
        int a, b;
        do {
            a = rand() % FATHER;
            b = rand() % FATHER;
        } while (a == b);
        player[i] = cross(player[a], player[b]);
    }
}

void initConsole() {
    system("chcp 65001");  //设置代码页为UTF-8
    SetConsoleTitleA("Console_迷宫");
    CONSOLE_CURSOR_INFO pos = {1, FALSE};
    SetConsoleCursorInfo(hOut, &pos);
}

void setPos(SHORT x, SHORT y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(hOut, pos);
}

void printMap() {
    system("cls");
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            printf(map[i][j] ? "#" : " ");
        }
        printf("\n");
    }
    printf("age:%d", age);
    setPos(yExit, xExit);
    printf("O");
}

void printPlayer(Player play) {
    play.x = 1;
    play.y = 1;
    for (int i = 0; i < GENE; ++i) {
        move(play, play.gene[i]);
        printMap();
        setPos(play.y, play.x);
        printf("@");
        if (play.x == xExit && play.y == yExit) {
            break;
        }
    }
    system("pause");
}
