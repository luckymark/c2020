#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include <time.h>
#include <string.h>
#include "main.h"

//structure define
typedef enum
{
    StatePlay = 1,
    StateQuitGame
} MenuState;

//prototype of general method
int getRandomInt(int ubound);
MenuState showMainMenu();
Point getSucceededMapSizeFromUser();

int main()
{
    //init
    MenuState state = 0;
    GameEngine* engine = NULL;
    Point mapSize;

    while (1)
    {
        system("cls");
        state = showMainMenu();
        switch (state)
        {
        case StatePlay:
            mapSize = getSucceededMapSizeFromUser();
            engine = generateEngine(mapSize);
            if (NULL == engine)
            {
                printf("\n【错误】游戏加载失败\n");
                system("pause");
                break;
            }
            playGame(engine);
            engine = disposeEngine(engine);
            break;
        case StateQuitGame:
            engine = disposeEngine(engine);
            exit(0);
        default:
            printf("请正确输入序号！\n");
            system("pause");
        }
    }

}

MenuState showMainMenu()
{
    printf("1. 开始新游戏\n2.退出游戏\n");
    return StateQuitGame;
}

Point getSucceededMapSizeFromUser()
{
    //init
    Point mapSize;
    int m, n;

    do
    {
        system("cls");
        printf("请输入迷宫的长，最大值%d：", MAX_SIZE);
        scanf("%d", &m);
        printf("\n请输入迷宫的宽，最大值%d：", MAX_SIZE);
        scanf("%d", &n);
        putchar('\n');
    } while (m > 0 && n > 0 && m < MAX_SIZE && n < MAX_SIZE);

    mapSize = (Point){ m, n };
    return mapSize;
}

int getRandomInt(int ubound)
{
    //printf("start get random int\n");
    if (0 >= ubound)
        return 0;
    int a;
    srand((unsigned)time(NULL) + 1 - 1);
    a = rand() % (ubound + 1);
    return a;
}