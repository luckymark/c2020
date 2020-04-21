#include "main.h"
#include <cstddef>

GameEngine* generateEngine(Point mapSize)
{
    /// using Randomized Prim's Algorithm to generate a m*n map

    //init
    GameEngine* engine = NewEngine(mapSize);
    int nodeCount = engine->mapSize.x * engine->mapSize.y;
    DisjointSet set = NewDisjointSet(nodeCount);
    int rdNode, rdNeighbor = 0;

    //generate
    do
    {
        rdNode = getRandomInt(nodeCount - 1);
        rdNeighbor = getNeighborNode(rdNode, engine->mapSize.x);
        if (findSet(&set, rdNeighbor) == findSet(&set, rdNode))
            continue;
        breakWall(engine, rdNode, rdNeighbor);
        unionSet(&set, rdNode, rdNeighbor);
    } while (findSet(&set, nodeCount - 1) != findSet(&set, 0));

    return engine;
}

GameEngine* NewEngine(Point mapSize)
{
    GameEngine* engine = malloc(sizeof(GameEngine));

    int m = mapSize.x;
    int n = mapSize.y;
    engine->mapSize = mapSize;
    engine->standOn = mapBit[space];

    //init map
    int i = 0, j = 0;
    for (i = 0; i < 2 * m + 1; i++)
        for (j = 0; j < 2 * n + 1; j++)
        {
            if (1 == i % 2 && 1 == j % 2)
                engine->map[i][j] = mapBit[space];
            else
                engine->map[i][j] = mapBit[wall];
        }

    //set Start Node And End Node
    engine->startPoint = (Point){ 1,0 };
    engine->endPoint = (Point){ 2 * m,2 * n + 1 };
    engine->map[engine->startPoint.x][engine->startPoint.y] = mapBit[startSignal];
    engine->map[engine->startPoint.x][engine->startPoint.y] = mapBit[endSignal];

    return engine;
}

int getNeighborNode(int node, int m)
{
    int rd = getRandomInt(100);
    if (rd < 25)
    {
        return node - 1;
    }
    else if (rd >= 25 && rd < 50)
    {
        return node + 1;
    }
    else if (rd >= 50 && rd < 75)
    {
        return node + m;
    }
    else
    {
        return node - m;
    }
}

void breakWall(GameEngine* engine, int node, int neighbor)
{
    int i = (node / engine->mapSize.x) + 1 + (neighbor / engine->mapSize.x);
    int j = (node % engine->mapSize.y) + 1 + (neighbor % engine->mapSize.y);
    engine->map[i][j] = mapBit[space];
}

DisjointSet NewDisjointSet(int count)
{
    DisjointSet result;
    memset(&result, 0, sizeof(DisjointSet));
    int i;
    for (i = 0; i < count; i++)
        result.set[i] = i;
    return result;
}

void unionSet(DisjointSet* pSet, int x, int y)
{
    if ((x = findSet(pSet, x)) == (y = findSet(pSet, y)))
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

int findSet(DisjointSet* pSet, int x)
{
    if (x < 0)
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

Point pointPlus(Point left, Point right)
{
    Point result;
    result.x = left.x + right.x;
    result.y = left.y + right.y;
    return result;
}

GameEngine* disposeEngine(GameEngine* engine)
{
    if (NULL != engine)
        free(engine);
    return NULL;
}