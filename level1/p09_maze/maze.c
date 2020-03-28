#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 99

//prototype
void Init();
int GenerateMap();
int GetRandomInt(int ubound);
int NewConnectionFrom(int node);
int GetStartNode();
void DeleteNodeByIndex(int index);
int IsAllNeighborAvailable(int node);
void AddNode(int node);
int IsOutOfMap(int x,int y);
void DrawMap();

//global
char map[MAX_SIZE][MAX_SIZE];
int m = 5,n = 5;
int list[MAX_SIZE * MAX_SIZE];
int list_tail = 0;

int main()
{
    Init();
    int start_node = GenerateMap();
    DrawMap();

    return 0;
}

void Init()
{
    //scanf_s("%d %d",&m,&n);

    int i = 0,j = 0;
    for(i = 0; i < 2 * m + 1; i++)
        for(j = 0; j < 2 * n + 1; j++)
        {
            // TODO fill node point with space char
            if(1 == i % 2 && 1 == j % 2)
                map[i][j] = ' ';
            else
                map[i][j] = '#';
        }

    printf("Initial map \n");
    DrawMap();
}

int GenerateMap()
{
    /// using Randomized Prim's Algorithm to generate a m*n map

    //init
    int tmp_index,tmp_node;
    int start_node = GetStartNode();
    AddNode(start_node);

    while(list_tail > 0)
    {
        tmp_index = GetRandomInt(list_tail - 1);
        tmp_node = list[tmp_index];

        //printf("tmp index = %d, tmp node = %d \n",tmp_index,tmp_node);

        if(1 == IsAllNeighborAvailable(tmp_node))
        {
            DeleteNodeByIndex(tmp_index);
            continue;
        }

        tmp_node = NewConnectionFrom(tmp_node);
        AddNode(tmp_node);
        DrawMap();
    }

    return start_node;
}

int NewConnectionFrom(int node)
{
    //printf("New connection from node %d \n",node);
    //init
    int neighbor_node = 0;
    int x = 1 + 2 * (node % m),y = 1 + 2 * (node / m);
    printf("x = %d, y = %d \n",x,y);
    int i,j,index;

    //search random neighbour
    while(1)
    {
        index = GetRandomInt(3);
        switch(index)
        {
            case 0:
                i = x+1;
                j = y;
                break;
            case 1:
                i = x-1;
                j = y;
                break;
            case 2:
                i = x;
                j = y+1;
                break;
            case 3:
                i = x;
                j = y-1;
                break;
            default:
                printf("switch error \n");
        }

        //printf("i = %d, j = %d \n",i,j);

        if(' ' != map[i][j] && 0 == IsOutOfMap(i,j))
        {
            map[i][j] = ' ';
            i = ((2 * i - x) - 1) / 2;
            j = ((2 * j - y) - 1) / 2;
            neighbor_node = m * j + i;
            return neighbor_node;
        }
    }
}

int GetStartNode()
{
    int start_node = 0;
    if(0 == GetRandomInt(1))
    {
        int i = GetRandomInt(m);
        start_node = i * n;
        map[2 * i + 1][0] = ' ';
    }
    else
    {
        int j = GetRandomInt(n);
        start_node = j;
        map[0][2 * j + 1] = ' ';
    }
    return start_node;
}

int IsAllNeighborAvailable(int node)
{
    //init
    int x = 1 + 2 * (node % m),y = 1 + 2 * (node / m);
    int i, j;

    if('#' == map[x+1][y] && 0 ==  IsOutOfMap(x+1,y))
        return 0;
    if('#' == map[x-1][y] && 0 ==  IsOutOfMap(x-1,y))
        return 0;
    if('#' == map[x][y+1] && 0 ==  IsOutOfMap(x,y+1))
        return 0;
    if('#' == map[x][y-1] && 0 ==  IsOutOfMap(x,y-1))
        return 0;

    printf("all neighbor of node %d is available \n",node);
    return 1;
}

void AddNode(int node)
{
    //printf("start add node %d \n",node);
    int k = GetRandomInt(list_tail - 1);
    //printf("stop get random int \n");
    list_tail++;
    list[list_tail-1] = list[k];
    list[k] = node;
}

void DeleteNodeByIndex(int index)
{
    list[index] = list[list_tail - 1];
    list_tail--;
}

int IsOutOfMap(int x,int y)
{
    if(x > 0 && x < 2 * m  && y > 0 && y < 2 * n)
        return 0;
    else
        return 1;
}

int GetRandomInt(int ubound)
{
    //printf("start get random int\n");
    if(0 >= ubound)
        return 0;
    int a;
    srand((unsigned)time(NULL));
    a = rand() % (ubound+1);
    return a;
}

void DrawMap()
{
    int i,j;
    for(i = 0;i <= 2*m;i++)
    {
        for(j = 0;j <= 2*n;j++)
            printf("%c ",map[i][j]);
        printf("\n");
    }
    printf("\n\n");
}