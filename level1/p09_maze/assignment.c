#include <conio.h>
#include <stdio.h>

#define ROW 15     // 15行
#define COLUMN 15  // 15列

void render();

//玩家 ♀   5
//墙壁 ■   4
//空地     0
//终点☆   9
int flag = 0;  //终点判定  1为到达终点

int Xp = 1;
int Yp = 1;
//玩家初始坐标（1，1）
int map[ROW][COLUMN] = {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                        {4, 5, 4, 0, 0, 0, 4, 4, 0, 0, 4, 0, 0, 0, 4},
                        {4, 0, 4, 4, 4, 0, 4, 0, 4, 0, 4, 0, 4, 0, 4},
                        {4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 0, 4, 0, 4},
                        {4, 0, 4, 4, 4, 0, 4, 0, 4, 0, 4, 0, 4, 0, 4},
                        {4, 0, 4, 0, 0, 0, 4, 0, 4, 0, 0, 0, 4, 0, 4},
                        {4, 0, 4, 0, 0, 4, 4, 4, 0, 4, 0, 4, 4, 0, 4},
                        {4, 0, 4, 4, 0, 4, 0, 0, 0, 4, 0, 0, 4, 0, 4},
                        {4, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 4, 0, 4},
                        {4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 4, 4, 4, 0, 4},
                        {4, 0, 0, 0, 4, 0, 0, 0, 0, 4, 4, 0, 0, 0, 4},
                        {4, 4, 4, 0, 4, 0, 4, 0, 4, 0, 0, 0, 4, 4, 4},
                        {4, 0, 4, 0, 4, 0, 4, 0, 4, 0, 4, 4, 9, 0, 4},
                        {4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4},
                        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};

//渲染器
void render() {
    //渲染地图：
    system("cls");
    printf("\n\n\n\n\n\n\n");
    for (int x = 0; x < ROW; x++) {
        printf("                                               ");
        for (int y = 0; y < COLUMN; y++) {
            switch (map[x][y]) {
                case 4:
                    printf("■");
                    break;
                case 5:
                    printf("♀");
                    break;
                case 9:
                    printf("☆");
                    break;
                default:
                    printf("  ");
            }
        }
        puts("");
    }
}

//移动控制器  并附带判定
void moveControler(int _Yp, int _Xp, int ch) {
    //开始读入下一个位置 并判定
    switch (ch) {
        case 72:
            _Yp--;
            if (map[_Yp][_Xp] == 4) return;  //判定有无阻挡 有的话返回
            Yp--;                            //没有的话才真正进行移动
            _Yp++;  //这里再加回去是为了擦除上一个位置
            break;
        case 80:
            _Yp++;
            if (map[_Yp][_Xp] == 4) return;
            Yp++;
            _Yp--;
            break;
        case 75:
            _Xp--;
            if (map[_Yp][_Xp] == 4) return;
            Xp--;
            _Xp++;
            break;

        case 77:
            _Xp++;
            if (map[_Yp][_Xp] == 4) return;
            Xp++;
            _Xp--;
            break;
    }
    map[_Yp][_Xp] = 0;  //上一个位置擦除

    if (map[Yp][Xp] == 9) flag = 1;
    map[Yp][Xp] = 5;  //绘制玩家坐标
}

void startGame() {
    system("cls");
    render();
    int ch = 32;
    while ((ch = getch()) != 26) {
        if (ch == 0xE0) {
            ch = getch();
            moveControler(Yp, Xp, ch);
        }
        render();
        if (flag == 1) {
            printf("\n\n\n\n\n");
            puts(
                "                               You've reached the "
                "destination!!");
            return;
        }
    }
}

int main(void) {
    system("chcp 65001");
    startGame();

    return 0;
}

