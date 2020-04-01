#include <conio.h>
#include <stdio.h>
#include <windows.h>
#define ROW 15     // 15行
#define COLUMN 15  // 15列
#define PLAYER 5
#define BOX 6

void render();
void moveControler_Box(int _Yp, int _Xp, int ch, int object);
void moveControler_Player(int _Yp, int _Xp, int ch, int object);
void readScore(int* score1, int* score2);
void writeScore();
void latestScoreList();
void loadMap(FILE *level);
void importMap();
int isWin();
void innerCourse();
int mainMenu();
void startGame();

//玩家 ㋡   5
//墙壁 ■   4
//空地     0
//终点☆   9
//箱子★   6
int nowlevel = 1, maxlevel = 2;  //目前的关卡 ，最大关卡（目前2）
int flag = 0;   //胜利判断  flag=总箱子数量=boxs时获胜
int steps = 0;  //步数
int boxs;
//玩家初始坐标
int Xp;
int Yp;
int MAP[ROW][COLUMN];
int map[ROW][COLUMN];

//渲染器
void render() {
    //渲染地图：
    system("cls");
    puts("Tips:You could press ESC to come back GameMenu.");
    printf("\n\n\n\n\n");
    printf("\t\t\t\t\t\tLevel: %d          Steps: %d\n\n", nowlevel, steps);

    //正式渲染
    for (int x = 0; x < ROW; x++) {
        printf("                                               ");
        for (int y = 0; y < COLUMN; y++) {
            switch (map[x][y]) {
                case 4:
                    printf("■");
                    break;
                case 5:
                    printf("㋡");
                    break;
                case 6:
                    printf("★");
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

void moveControler_Box(int _Yp, int _Xp, int ch, int object) {
    switch (ch) {
        case 72:
            _Yp--;
            break;
        case 80:
            _Yp++;
            break;
        case 75:
            _Xp--;
            break;
        case 77:
            _Xp++;
            break;
    }
    if (map[_Yp][_Xp] == 9) flag++;  //如果箱子移进目标 则胜利判断加一
    map[_Yp][_Xp] = object;          //绘制对象坐标
}

//移动控制器  并附带判定 (初始y坐标，初始x坐标，目标移向，移动对象)
//待改进：功能太杂揉了
void moveControler_Player(int _Yp, int _Xp, int ch, int object) {
    //开始读入下一个位置 并判定
    switch (ch) {
        case 72:
            _Yp--;
            //判定有无阻挡 有的话返回
            if ((map[_Yp][_Xp] == 6) && (map[_Yp - 1][_Xp] != 6) &&
                (map[_Yp - 1][_Xp] != 4)) {
                moveControler_Box(_Yp, _Xp, ch, BOX);
                if (MAP[_Yp][_Xp] == 9)
                    flag--;  //如果箱子从目标点移出来 则胜利判断减一
                map[_Yp][_Xp] = 0;  //擦除箱子
            }
            if ((map[_Yp][_Xp] == 4) || (map[_Yp][_Xp] == 6)) return;
            Yp--;   //没有的话才真正进行移动
            _Yp++;  //这里再加回去是为了擦除上一个位置
            break;
        case 80:
            _Yp++;
            if ((map[_Yp][_Xp] == 6) && (map[_Yp + 1][_Xp] != 6) &&
                (map[_Yp + 1][_Xp] != 4)) {
                moveControler_Box(_Yp, _Xp, ch, BOX);
                if (MAP[_Yp][_Xp] == 9) flag--;
                map[_Yp][_Xp] = 0;
            }
            if ((map[_Yp][_Xp] == 4) || (map[_Yp][_Xp] == 6)) return;
            Yp++;
            _Yp--;
            break;
        case 75:
            _Xp--;
            if ((map[_Yp][_Xp] == 6) && (map[_Yp][_Xp - 1] != 6) &&
                (map[_Yp][_Xp - 1] != 4)) {
                moveControler_Box(_Yp, _Xp, ch, BOX);
                if (MAP[_Yp][_Xp] == 9) flag--;
                map[_Yp][_Xp] = 0;
            }
            if ((map[_Yp][_Xp] == 4) || (map[_Yp][_Xp] == 6)) return;
            Xp--;
            _Xp++;
            break;

        case 77:
            _Xp++;
            if ((map[_Yp][_Xp] == 6) && (map[_Yp][_Xp + 1] != 6) &&
                (map[_Yp][_Xp + 1] != 4)) {
                moveControler_Box(_Yp, _Xp, ch, BOX);
                if (MAP[_Yp][_Xp] == 9) flag--;
                map[_Yp][_Xp] = 0;
            }
            if ((map[_Yp][_Xp] == 4) || (map[_Yp][_Xp] == 6)) return;
            Xp++;
            _Xp--;
            break;
    }
    if (MAP[_Yp][_Xp] == 9)
        map[_Yp][_Xp] = 9;
    else
        map[_Yp][_Xp] = 0;  //上一个位置擦除

    map[Yp][Xp] = object;  //绘制对象坐标
    steps++;
    render();
}

void readScore(int* score1,int* score2) {
    FILE *Score;
    Score=fopen("score1.txt","r");
    fscanf(Score, "%d",score1);
    Score=fopen("score2.txt","r");
    fscanf(Score, "%d",score2);

    fclose(Score);
}

void writeScore() {
    FILE *Score;
    switch (nowlevel) {
        case 1:
            Score = fopen("score1.txt", "w");
            break;
        case 2:
            Score = fopen("score2.txt", "w");
            break;
    }
    fprintf(Score, "%d ", steps);
    fclose(Score);
}

void latestScoreList(){
    int score1 = 0, score2 = 0;
    readScore(&score1,&score2);
    system("cls");
    printf("\n\n\n\n\nThe latest score of each level:");
    printf("\nLevel: %d",score1);
    printf("\nLeve2: %d",score2);
    getch();
}

//步骤2:读入地图（前15x15个数字） 箱子个数 初始横纵坐标
void loadMap(FILE *level) {
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COLUMN; j++) {
            fscanf(level, "%d", &MAP[i][j]);
            map[i][j] = MAP[i][j];
        }

    fscanf(level, "%d", &boxs);
    fscanf(level, "%d", &Xp);
    fscanf(level, "%d", &Yp);
    //设置每张地图初始步数、通关判断旗
    flag = 0;
    steps = 0;

    //加载地图成功后完成初始化渲染
    render();  //初始化地图
}

//步骤1:导入地图文件
void importMap() {
    FILE *level;
    //关卡选择
    switch (nowlevel) {
        case 1:
            level = fopen("level1.txt", "r");
            break;
        case 2:
            level = fopen("level2.txt", "r");
            break;
    }

    //地图读取判断
    if (level == NULL) {
        puts("ERROR:Map loading failed.");
        return;
    };

    //导入地图文件成功后开始加载地图
    loadMap(level);
}

//每个关卡获胜判断 & 通关判断（通关为1 否则为0）
int isWin() {
    if (flag == boxs) {
        //在此调用写入得分
        writeScore();

        nowlevel++;
        printf("                        You win and your steps is: %d\n",
               steps);
        Sleep(500);

        //通关判断：没有下一关的话执行通关过程
        if (nowlevel > maxlevel) {
            Sleep(500);
            puts(
                "                               "
                "...................................");
            Sleep(500);
            system("cls");
            printf("\n\n\n\n\n\n\n");
            puts(
                "                              YOU HAVE FINISH ALL THE "
                "MISSIONS!  "
                "CONGRATULATIONS!      ");
            Sleep(2000);
            return 1;
        }
        //进入下一关 读取新的地图
        puts("                        Loading next level...");
        Sleep(1500);
        importMap();
    }
    return 0;
}

//关卡内部进程 （与具体地图文件无关）
void innerCourse() {
    system("color 7C");
    nowlevel = 1;   //每次进入游戏时从第一关开始
    importMap();    //导入第一关地图
    int flag2 = 0;  //通关判断旗

    int ch = 32;  //初始化读入符为空格 32

    //开始阻塞式键盘监听 游戏主进程开始执行
    while ((ch = getch()) != 27) {
        if (ch == 0xE0) {
            ch = getch();
            moveControler_Player(Yp, Xp, ch, PLAYER);
        }
        if ((flag2 = isWin()) == 1)
            return;  //如果过关 则进入一下关，如果通关 则退出关卡内部进程
    }
}



//开始菜单
int mainMenu() {
    typedef enum options { START, RECORD, QUITGAME } options;

    options menuOption = 0;  //默认光标停留在开始游戏

    //读取最终的选择 期间玩家上下键来更改
    int hit = 32;
    system("color 80");
    do {
        system("cls");
        if (hit == 0xE0) {
            hit = getch();
            // 72为上 80为下
            if (hit == 72) {
                menuOption = (menuOption - 1);
                if (menuOption == -1) menuOption = 2;
            } else if (hit == 80) {
                menuOption = (menuOption + 1) % 3;
            }
        }
        printf("\n\n\n\n");
        printf(
            "\t\t\t\t######  #     #  #####  #     #       ######  ####### #   "
            "  #\n");
        printf(
            "\t\t\t\t#     # #     # #     # #     #       #     # #     #  #  "
            " # \n");
        printf(
            "\t\t\t\t#     # #     # #       #     #       #     # #     #   # "
            "#  \n");
        printf(
            "\t\t\t\t######  #     #  #####  ####### ##### ######  #     #    "
            "#   \n");
        printf(
            "\t\t\t\t#       #     #       # #     #       #     # #     #   # "
            "#  \n");
        printf(
            "\t\t\t\t#       #     # #     # #     #       #     # #     #  #  "
            " # \n");
        printf(
            "\t\t\t\t#        #####   #####  #     #       ######  ####### #   "
            "  #\n");

        printf("\n\n\n\t\t\t\t\t\t\t");
        if (menuOption == 0) printf("▶ ");
        printf("Start\n\n");

        printf("\t\t\t\t\t\t\t");
        if (menuOption == 1) printf("▶ ");
        printf("The latest scores\n\n");

        printf("\t\t\t\t\t\t\t");
        if (menuOption == 2) printf("▶ ");
        printf("Quit\n\n");

        printf("\n\n\t\t\t\t\t\t\t\t\t\t Ver1.0   by TeaRanger\n");
    } while ((hit = getch()) != 13);  //按下回车即 读取完毕

    //执行对应操作
    switch (menuOption) {
        case START:
            innerCourse();
            break;
        case RECORD:
            latestScoreList();
            break;
        case QUITGAME:
            return -1;
    }
    return 1;
}

//小游戏主体
void startGame() {
    int a = 1;
    while (a != -1) {
        a = mainMenu();
    }
}

// main函数
int main(void) {
    system("chcp 65001");
    system("cls");
    startGame();

    return 0;
}
