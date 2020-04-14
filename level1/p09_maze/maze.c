#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include <time.h>
#include <string.h>

#define MAX_SIZE 99

//structure define
typedef enum
{
    space = 0,
    wall,
    player,
    startSignal,
    endSignal
} MapBitType;
char mapBit[5] = {' ','#','P','A','B'};
typedef struct
{
    int x;
    int y;
} Point;
typedef enum
{
    StatePlay = 1,
    StateQuitGame
} MenuState;
typedef struct
{
    char map[MAX_SIZE][MAX_SIZE];
    Point point, startPoint, endPoint,mapSize,tmpPoint;
    char standOn;
} GameEngine;
typedef struct
{
    int set[MAX_SIZE * MAX_SIZE];
} DisjointSet;

//prototype of point and engine method
GameEngine *generateEngine(Point mapSize);
Point pointPlus(Point left, Point right);
GameEngine * NewEngine(Point mapSize);
GameEngine *disposeEngine(GameEngine *engine);

//prototype of map generator
int findSet(DisjointSet *pSet, int x);
void unionSet(DisjointSet *pSet, int x, int y);
DisjointSet NewDisjointSet(int count);
void breakWall(GameEngine *engine, int node, int neighbor);
int getNeighborNode(int node, int m);

//prototype of game logic
int isPlayerBlocked(GameEngine *engine);
void drawMap(GameEngine *engine);
void playGame(GameEngine *engine);
int isWon(GameEngine *engine);
Point getMovement(int ch);
void walk(GameEngine *engine);

//prototype of general method
int getRandomInt(int ubound);
MenuState showMainMenu();
Point getSucceededMapSizeFromUser();

int main()
{
    //init
    MenuState state = 0;
    GameEngine * engine = NULL;
    Point mapSize;

    while(1)
    {
        system("cls");
        state = showMainMenu();
        switch(state)
        {
            case StatePlay:
                mapSize = getSucceededMapSizeFromUser();
                engine = generateEngine(mapSize);
                if(NULL == engine)
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
void playGame(GameEngine *engine)
{
    //init
    int ch;
    Point tmpMove;
    drawMap(engine);

    //play
    while (1)
    {
        ch = _getch();
        tmpMove = getMovement(ch);
        engine->tmpPoint = pointPlus(engine->point, tmpMove);

        if(isPlayerBlocked(engine))
            continue;
        walk(engine);
        if(isWon(engine))
            break;
    }

    //show win message
    printf("\n\n\nCongratulation!\n");
    system("pause");
}

void walk(GameEngine *engine)
{
    engine->map[engine->point.x][engine->point.y] = engine->standOn;
    engine->standOn = engine->map[engine->tmpPoint.x][engine->tmpPoint.y];
    engine->map[engine->tmpPoint.x][engine->tmpPoint.y] = mapBit[player];
    engine->point = engine->tmpPoint;

    drawMap(engine);
}

int isWon(GameEngine *engine)
{
    if(engine->endPoint.x != engine->point.x)
        return 0;
    if(engine->endPoint.y != engine->point.y)
        return 0;
    return 1;
}

int isPlayerBlocked(GameEngine *engine)
{
    if(engine->map[engine->tmpPoint.x][engine->tmpPoint.y] == mapBit[wall])
        return 1;

    if(!(engine->point.x > 0 && engine->point.x < 2 * engine->mapSize.x
         && engine->point.y > 0 && engine->point.y < 2 * engine->mapSize.y))
        return 1;

    return 0;
}

GameEngine * generateEngine(Point mapSize)
{
    /// using Randomized Prim's Algorithm to generate a m*n map

    //init
    GameEngine * engine = NewEngine(mapSize);
    int nodeCount = engine->mapSize.x * engine->mapSize.y;
    DisjointSet set = NewDisjointSet(nodeCount);
    int rdNode,rdNeighbor = 0;

    //generate
    do
    {
        rdNode = getRandomInt(nodeCount-1);
        rdNeighbor = getNeighborNode(rdNode, engine->mapSize.x);
        if(findSet(&set,rdNeighbor) == findSet(&set, rdNode))
            continue;
        breakWall(engine,rdNode,rdNeighbor);
        unionSet(&set, rdNode, rdNeighbor);
    }while (findSet(&set,nodeCount-1) != findSet(&set, 0));

    return engine;
}

GameEngine * NewEngine(Point mapSize)
{
    GameEngine *engine = malloc(sizeof(GameEngine));

    int m = mapSize.x;
    int n = mapSize.y;
    engine->mapSize = mapSize;
    engine->standOn = mapBit[space];

    //init map
    int i = 0,j = 0;
    for(i = 0; i < 2 * m + 1; i++)
        for(j = 0; j < 2 * n + 1; j++)
        {
            if(1 == i % 2 && 1 == j % 2)
                engine->map[i][j] = mapBit[space];
            else
                engine->map[i][j] = mapBit[wall];
        }

    //set Start Node And End Node
    engine->startPoint = (Point){1,0};
    engine->endPoint = (Point){2 * m,2 * n + 1};
    engine->map[engine->startPoint.x][engine->startPoint.y] = mapBit[startSignal];
    engine->map[engine->startPoint.x][engine->startPoint.y] = mapBit[endSignal];

    return engine;
}

int getNeighborNode(int node, int m)
{
    int rd = getRandomInt(100);
    if(rd< 25)
    {
        return node - 1;
    } else if (rd >= 25 && rd < 50)
    {
        return node + 1;
    } else if (rd >= 50 && rd < 75)
    {
        return node + m;
    } else
    {
        return node - m;
    }
}

void breakWall(GameEngine * engine, int node, int neighbor)
{
    int i = (node / engine->mapSize.x) + 1 + (neighbor / engine->mapSize.x);
    int j = (node % engine->mapSize.y) + 1 + (neighbor % engine->mapSize.y);
    engine->map[i][j] = mapBit[space];
}

DisjointSet NewDisjointSet(int count)
{
    DisjointSet result;
    memset(&result,0, sizeof(DisjointSet));
    int i;
    for(i = 0;i<count;i++)
        result.set[i] = i;
    return result;
}

void unionSet(DisjointSet *pSet, int x, int y)
{
    if ((x = findSet(pSet,x)) == (y = findSet(pSet,y)))
        return;
    if (pSet->set[x] < pSet->set[y])
    {
        pSet->set[x] += pSet->set[y];
        pSet->set[y] = x;
    }
    else
    {
        pSet->set[y] += pSet->set[x];
        pSet->set[x] = y;
    }
}

int findSet(DisjointSet *pSet, int x)
{
    if(x < 0)
        return -1;

    int root = x, t;
    while (pSet->set[root] > 0)
        root = pSet->set[root];
    while (x != root)
    {
        t = pSet->set[x];
        pSet->set[x] = root;
        x = t;
    }
    return x;
}

Point getSucceededMapSizeFromUser()
{
    //init
    Point mapSize;
    int m,n;

    do
    {
        system("cls");
        printf("请输入迷宫的长，最大值%d：",MAX_SIZE);
        scanf("%d",&m);
        printf("\n请输入迷宫的宽，最大值%d：",MAX_SIZE);
        scanf("%d",&n);
        putchar('\n');
    } while (m > 0 && n > 0 && m < MAX_SIZE && n < MAX_SIZE);

    mapSize = (Point){m, n};
    return mapSize;
}

MenuState showMainMenu()
{
    printf("1. 开始新游戏\n2.退出游戏\n");
    return StateQuitGame;
}

int getRandomInt(int ubound)
{
    //printf("start get random int\n");
    if(0 >= ubound)
        return 0;
    int a;
    srand((unsigned)time(NULL)+1-1);
    a = rand() % (ubound+1);
    return a;
}

void drawMap(GameEngine *engine)
{
    int i,j;
    for(i = 0;i <= 2 * engine->mapSize.x; i++)
    {
        for(j = 0;j <= 2 * engine->mapSize.y; j++)
            printf("%c ", engine->map[i][j]);
        printf("\n");
    }
    printf("\n\n");
}

Point pointPlus(Point left, Point right)
{
    Point result;
    result.x = left.x + right.x;
    result.y = left.y + right.y;
    return result;
}

GameEngine *disposeEngine(GameEngine *engine)
{
    if(NULL != engine)
        free(engine);
    return NULL;
}

Point getMovement(int ch)
{
    //get tmp point
    Point tmpPoint = {0,0};

    if (0 == ch || 224 == ch)
    {
        // Use arrow keys
        switch (getch())
        {
            case 72: // Up
                tmpPoint = (Point) {.x = -1, .y =  0};
                break;

            case 80: // Down
                tmpPoint = (Point) {.x =  1, .y =  0};
                break;

            case 77: // Right
                tmpPoint = (Point) {.x =  0, .y =  1};
                break;

            case 75: // Left
                tmpPoint = (Point) {.x =  0, .y = -1};
                break;

            default:
                break;
        }
    }
    else
    {
        // Use w a s d
        switch (ch)
        {
            case 'w':
            case 'W': // Up
                tmpPoint = (Point) {.x = -1, .y =  0};
                break;

            case 's':
            case 'S': // Down
                tmpPoint = (Point) {.x =  1, .y =  0};
                break;

            case 'd':
            case 'D': // Right
                tmpPoint = (Point) {.x =  0, .y =  1};
                break;

            case 'a':
            case 'A': // Left
                tmpPoint = (Point) {.x =  0, .y = -1};
                break;

            default:
                break;
        }
    }
    return tmpPoint;
}
