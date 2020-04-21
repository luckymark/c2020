//const
#define MAX_SIZE 99

//struct and enum
typedef enum
{
    space = 0,
    wall,
    player,
    startSignal,
    endSignal
} MapBitType;
char mapBit[5] = { ' ','#','P','A','B' };
typedef struct
{
    int x;
    int y;
} Point;
typedef struct
{
    char map[MAX_SIZE][MAX_SIZE];
    Point point, startPoint, endPoint, mapSize, tmpPoint;
    char standOn;
} GameEngine;
typedef struct
{
    int set[MAX_SIZE * MAX_SIZE];
} DisjointSet;

//prototype of game logic
int isPlayerBlocked(GameEngine* engine);
void drawMap(GameEngine* engine);
void playGame(GameEngine* engine);
int isWon(GameEngine* engine);
Point getMovement(int ch);
void walk(GameEngine* engine);

//prototype of point and engine method
GameEngine* generateEngine(Point mapSize);
Point pointPlus(Point left, Point right);
GameEngine* NewEngine(Point mapSize);
GameEngine* disposeEngine(GameEngine* engine);

//prototype of map generator
int findSet(DisjointSet* pSet, int x);
void unionSet(DisjointSet* pSet, int x, int y);
DisjointSet NewDisjointSet(int count);
void breakWall(GameEngine* engine, int node, int neighbor);
int getNeighborNode(int node, int m);