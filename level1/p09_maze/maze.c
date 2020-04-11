#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include <time.h>
#define MAX_SIZE 99

//structure define
typedef enum
{
    space = 0,
    wall = 1,
    player = 2
} MapBitType;
char mapBit[3] = {' ','#','*'};
typedef struct
{
    int x;
    int y;
} Point;
typedef struct
{
    char map[MAX_SIZE][MAX_SIZE];
    int m,n;
    Point point, start_point, end_point;
} GameEngine;
typedef struct
{
    GameEngine* engine;
    int list[MAX_SIZE * MAX_SIZE];
    int list_tail;
} GameEngineGenerator;

//global
Point MOVEMENT[23] = {
        (Point){.x = -1,.y =  0}, //key a, go left
        (Point){.x =  0,.y =  0},
        (Point){.x =  0,.y =  0},
        (Point){.x =  1,.y =  0}, //key d, go right
        (Point){.x =  0,.y =  0},
        (Point){.x =  0,.y = -1}, //arrow up    -> getch = 72
        (Point){.x =  0,.y =  0},
        (Point){.x =  0,.y =  0},
        (Point){.x = -1,.y =  0}, //arrow left  -> getch = 75
        (Point){.x =  0,.y =  0},
        (Point){.x =  1,.y =  0}, //arrow right -> getch = 77
        (Point){.x =  0,.y =  0},
        (Point){.x =  0,.y =  0},
        (Point){.x =  0,.y =  1}, //arrow down  -> getch = 80
        (Point){.x =  0 ,.y = 0},
        (Point){.x =  0,.y =  0},
        (Point){.x =  0,.y =  0},
        (Point){.x =  0,.y =  0},
        (Point){.x =  0,.y =  1}, //key s, go down
        (Point){.x =  0,.y =  0},
        (Point){.x =  0,.y =  0},
        (Point){.x =  0,.y =  0},
        (Point){.x =  0,.y = -1}  //key w, go up
};

//prototype
GameEngine * generateMap(int m, int n);
int getRandomInt(int ubound);
int isOutOfMap(GameEngine *engine, Point point);
void drawMap(GameEngine *engine);
void initGameEngine(GameEngine *engine, int m, int n);
void playGame(GameEngine *engine);
int isWon(GameEngine *engine);
void move(GameEngine *engine, int ch);

int main()
{
    //get m n and generate game engine
    int m,n;
    printf("请输入迷宫的长，最大值%d：",MAX_SIZE);
    scanf("%d",&m);
    printf("\n请输入迷宫的宽，最大值%d：",MAX_SIZE);
    scanf("%d",&n);
    putchar('\n');
    GameEngine* engine = generateMap(m, n);
    drawMap(engine);

    //play
    playGame(engine);

    //quit game
    free(engine);

    return 0;
}

void playGame(GameEngine *engine)
{
    int ch;
    while (1)
    {
        ch = _getch();
        move(engine,ch);
        if(isWon(engine))
            break;
    }

}

void move(GameEngine *engine, int ch)
{
    /* TODO add remark to this function and fix magic number
     *
     * */

    //get tmp point
    Point tmpPoint;
    if(0 == ch || 224 == ch)
        tmpPoint = MOVEMENT[_getch() - 72 + 5];
    else if(ch < 'a')
        tmpPoint = MOVEMENT[ch - 'a' - 26];
    else
        tmpPoint = MOVEMENT[ch - 'a'];
    tmpPoint = (Point){.x= tmpPoint.x + engine->point.x, .y = tmpPoint.y + engine->point.y};

    // don't move when meets wall
    if(mapBit[wall] == engine->map[tmpPoint.x][tmpPoint.y])
        return;

    engine->point = tmpPoint;

}

int isWon(GameEngine *engine)
{
    if(engine->end_point.x != engine->point.x)
        return 0;
    if(engine->end_point.y != engine->point.y)
        return 0;
    return 1;
}

GameEngine * generateMap(int m, int n)
{
    /// using Randomized Prim's Algorithm to generate a m*n map

    //init
    GameEngine *  result = malloc(sizeof(GameEngine));
    initGameEngine(result, m, n);
    GameEngineGenerator generator;
    generator.engine = result;
    generator.list_tail = 0;

    //generate

    return result;
}

void initGameEngine(GameEngine *engine, int m, int n)
{
    engine->m = m;
    engine->n = n;

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
    if(0 == getRandomInt(1))
    {
        i = getRandomInt(m);
        engine->start_point.x = 2 * i + 1;
        engine->start_point.y = 0;
        engine->map[2 * i + 1][0] = mapBit[space];
    }
    else
    {
        j = getRandomInt(n);
        engine->start_point.x = 0;
        engine->start_point.y = 2 * j + 1;
        engine->map[0][2 * j + 1] = mapBit[wall];
    }

}

int isOutOfMap(GameEngine *engine, Point point)
{
    if(point.x > 0 && point.x < 2 * engine->m && point.y > 0 && point.y < 2 * engine->n)
        return 0;
    else
        return 1;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
int getRandomInt(int ubound)
{
    //printf("start get random int\n");
    if(0 >= ubound)
        return 0;
    int a;
    srand((unsigned)time(NULL)+1-1);
    a = rand() % (ubound+1); // NOLINT(cert-msc30-c)
    return a;
}
#pragma clang diagnostic pop

void drawMap(GameEngine *engine)
{
    int i,j;
    for(i = 0;i <= 2 * engine->m; i++)
    {
        for(j = 0;j <= 2 * engine->n; j++)
            printf("%c ", engine->map[i][j]);
        printf("\n");
    }
    printf("\n\n");
}
