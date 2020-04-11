#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h"

//const
#define MAX_SIZE 99
#define DATA_FILENAME "data"
#define MAX_LEVEL 5

//struct
typedef enum
{
    space = 0,
    wall = 1,
    player = 2,
    box = 3,
    target = 4,
    succeededBox = 5
} MapBitType;
char mapBit[6] = {' ','#','P','@','x','O'};
typedef enum
{
    selectLevel = 1,
    tutorial,
    quitGame
} MenuState;
typedef struct
{
    int x;
    int y;
} Point;
typedef struct
{
    Point point, mapSize,tmpPoint;
    int stepCounter,restBox;
    char map[MAX_SIZE][MAX_SIZE];
    char standOn;
} GameEngine;

//prototype of object construction
GameEngine *getEngineFromFile(char level);
GameEngine *disposeEngine(GameEngine *engine);
GameEngine *newEngine(Point mapSize);
Point pointPlus(Point left, Point right);
void setFileName(char fileName[], char level);
FILE *getSucceededFilePtr(char level);
void readMapByFp(GameEngine *engine, FILE *fp);

//prototype of game logic
void drawMap(GameEngine *engine);
void playGame(GameEngine *engine);
int isWon(GameEngine *engine);
Point getMovement(int ch);
int isPlayerBlocked(GameEngine *engine);
void pushBox(GameEngine *engine);
void walk(GameEngine *engine);

//prototype of console
MenuState showMainMenuAndGetState();
int getSelectedLevel();
void showTutorial();

int main()
{
    //init
    int level = 0;
    MenuState state = 0;
    GameEngine * engine = NULL;

    while(1)
    {
        system("cls");
        state = showMainMenuAndGetState();
        switch(state)
        {
            case selectLevel:
                level = getSelectedLevel();
                engine = getEngineFromFile((char) level);
                if(NULL == engine)
                {
                    printf("Game load failed.\n");
                    system("pause");
                    break;
                }
                playGame(engine);
                engine = disposeEngine(engine);
                break;
            case tutorial:
                showTutorial();
                system("pause");
                break;
            case quitGame:
                engine = disposeEngine(engine);
                exit(0);
            default:
                printf("请正确输入序号！\n");
                system("pause");
        }
    }
}

void showTutorial()
{
    //TODO
}

GameEngine *disposeEngine(GameEngine *engine)
{
    free(engine);
    return NULL;
}

int getSelectedLevel()
{
    system("cls");

    printf("Please select a level from 1 to %d : \n",MAX_LEVEL);

    int result = 1;
    scanf("%d",&result);
    return result;
}

MenuState showMainMenuAndGetState()
{
    printf("Please select an option: \n1. select a level and play \n2. quit game \n");
    int a;
    scanf("%d",&a);
    switch (a)
    {
        case 1:
            return selectLevel;
        case 2:
            return quitGame;
        default:
            return 0;
    }
}

GameEngine *getEngineFromFile(char level)
{
    //get fp
    GameEngine * engine = NULL;
    FILE *fp = NULL;
    fp = getSucceededFilePtr(level);
    if(NULL == fp)
        return NULL;

    //get engine
    int m,n;
    fscanf(fp, "%d%d", &m, &n);
    engine = newEngine((Point) {m, n});
    readMapByFp(engine, fp);
    engine->map[1][1] = mapBit[player];

    fclose(fp);
    return engine;
}

void readMapByFp(GameEngine *engine, FILE *fp)
{
    int i,j,m,n;
    char tmp;
    m = engine->mapSize.x + 2;
    n = engine->mapSize.y + 2;

    for(i = 0;i < m;i++)
    {
        for(j = 0;j < n;j++)
        {
            do
                fscanf(fp,"%c",&tmp);
            while ('\n' == tmp);
            engine->map[i][j] = tmp;
            if(engine->map[i][j] == mapBit[box])
                engine->restBox++;
        }
    }
}

FILE *getSucceededFilePtr(char level)
{
    FILE *fp = NULL;
    errno_t err;

    //set file name
    char fileName[12] = DATA_FILENAME;
    if(level < 0 || level >= 100)
        return NULL;
    setFileName(fileName,level);

    //try open file
    err = fopen_s(&fp, fileName, "r");
    if(0 == err)
        return fp;
    return NULL;
}

GameEngine *newEngine(Point mapSize)
{
    GameEngine * engine = (GameEngine* )malloc(sizeof(GameEngine));
    engine->standOn = mapBit[space];
    engine->point = (Point){.x = 1,.y = 1};
    engine->tmpPoint = (Point){.x = 1,.y = 1};
    engine->stepCounter = 0;
    engine->restBox = 0;
    engine->mapSize.x = mapSize.x-2;
    engine->mapSize.y = mapSize.y-2;

    return engine;
}

void setFileName(char fileName[], char level)
{
    if(level < 10)
    {
        int l = (int)strlen(fileName);
        fileName[l] = (char)('0' + level);
        fileName[l+1] = '\0';
    }
    else
    {
        int a = level / 10,b = level % 10;
        int l = (int)strlen(fileName);
        fileName[l] = (char)a;
        fileName[l+1] = (char)b;
        fileName[l+2] = '\0';
    }
    strcat(fileName,".txt");
}

void drawMap(GameEngine *engine)
{
    system("cls");
    printf("steps taken: %d     rest boxes: %d\n", engine->stepCounter, engine->restBox);

    int i,j;
    for(i = 0;i < engine->mapSize.x + 2; i++)
    {
        for(j = 0;j < engine->mapSize.y + 2; j++)
            {printf("%c ", engine->map[i][j]);}
        printf("\n");
    }
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

        if(engine->map[engine->tmpPoint.x][engine->tmpPoint.y] == mapBit[box])
        {
            pushBox(engine);
            if(isWon(engine))
                break;
        }
        else
            walk(engine);
    }

    //show winner message
    printf("\n\n\nYou win! \nsteps: %d \n\n",engine->stepCounter);
    system("pause");
}

void walk(GameEngine *engine)
{
    engine->map[engine->point.x][engine->point.y] = engine->standOn;
    engine->standOn = engine->map[engine->tmpPoint.x][engine->tmpPoint.y];
    engine->map[engine->tmpPoint.x][engine->tmpPoint.y] = mapBit[player];
    engine->point = engine->tmpPoint;
    engine->stepCounter++;

    drawMap(engine);
}

void pushBox(GameEngine *engine)
{
    //init
    Point tmpMove = {.x = engine->tmpPoint.x - engine->point.x, .y = engine->tmpPoint.y - engine->point.y};

    //update map
    engine->map[engine->point.x][engine->point.y] = engine->standOn;
    engine->standOn = mapBit[space];
    engine->map[engine->tmpPoint.x][engine->tmpPoint.y] = mapBit[player];
    if(engine->map[engine->tmpPoint.x + tmpMove.x][engine->tmpPoint.y + tmpMove.y] == mapBit[target])
    {
        engine->map[engine->tmpPoint.x + tmpMove.x][engine->tmpPoint.y + tmpMove.y] = mapBit[succeededBox];
        engine->restBox--;
    }
    else
        engine->map[engine->tmpPoint.x + tmpMove.x][engine->tmpPoint.y + tmpMove.y] = mapBit[box];

    //update engine
    engine->point = engine->tmpPoint;
    engine->stepCounter++;

    drawMap(engine);
}

int isPlayerBlocked(GameEngine *engine)
{
    Point tmpMove = {.x = engine->tmpPoint.x - engine->point.x, .y = engine->tmpPoint.y - engine->point.y};
    if(engine->map[engine->tmpPoint.x][engine->tmpPoint.y] == mapBit[wall])
    {
        return 1;
    }
    if(engine->map[engine->tmpPoint.x][engine->tmpPoint.y] == mapBit[box]
    && engine->map[engine->tmpPoint.x + tmpMove.x][engine->tmpPoint.y + tmpMove.y] == mapBit[wall])
    {
        return 1;
    }

    return 0;
}

Point pointPlus(Point left, Point right)
{
    Point result;
    result.x = left.x + right.x;
    result.y = left.y + right.y;
    return result;
}

int isWon(GameEngine *engine)
{
    if(engine->restBox <= 0)
        return 1;

    return 0;
}