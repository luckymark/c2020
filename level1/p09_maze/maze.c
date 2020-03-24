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

//global
char map[MAX_SIZE][MAX_SIZE];
int m = 0,n = 0;
int list[MAX_SIZE * MAX_SIZE];
int list_tail = 0;

int main()
{
    Init();
    int start_node = GenerateMap();

}

void Init()
{
    int i = 0,j = 0;
    for(i = 0; i < MAX_SIZE; i++)
        for(j = 0; j < MAX_SIZE; j++)
            map[i][j] = '#';
}

int GenerateMap()
{
    /// using Randomized Prim's Algorithm to generate a m*n map

    //init
    int tmp_index,tmp_node;
    int start_node = GetStartNode();

    while(list_tail > 0)
    {
        tmp_index = GetRandomInt(list_tail - 1);
        tmp_node = list[tmp_index];

        if(1 == IsAllNeighborAvailable(tmp_node))
        {
            DeleteNodeByIndex(tmp_index);
            continue;
        }

        tmp_node = NewConnectionFrom(tmp_node);
        AddNode(tmp_node);
    }

    return start_node;
}

int NewConnectionFrom(int node)
{
    //init
    int neighbor_node = 0;
    int x = 1 + 2 * (node % m),y = 1 + 2 * (node / m);
    int dx[2] = {x-1,x+1}, dy[2] = {y-1,y+1};
    int i,j;

    //search random neighbour
    while(1)
    {
        i = dx[GetRandomInt(1)];
        j = dy[GetRandomInt(1)];
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

    for(i = -1;i<=1;i+=2)
        for(j = -1;j<=1;j+=2)
            if('#' == map[x+i][y+j] && 0 == IsOutOfMap(x+i,y+j))
            {return 0;}

    return 1;
}

void AddNode(int node)
{
    int k = GetRandomInt(list_tail - 1);
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
    if(0 == ubound)
        return 0;
    int a;
    srand((unsigned)time(NULL));
    a = rand() % (ubound+1);
    return a;
}