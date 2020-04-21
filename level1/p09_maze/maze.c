#include "maze.h"

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

