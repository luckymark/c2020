#include <stdio.h>
#include <stdlib.h>
#include "GA_.h"
#include <time.h>


int main()
{
    time_t start = time(NULL);
    int maze[LINE][ROW] ={
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,1,0,0,1,1,1,1,1,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1},
        {1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,1,1,0,1},
        {1,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1},
        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1},
        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1},
        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,2},
        {1,0,1,1,1,1,1,0,1,0,0,0,0,0,0,1,0,0,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1},
        {1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    people* peoples = (people*)malloc(sizeof(people) * POPULATION_SIZE);
    if( peoples == NULL ) {
        exit(-8);
    }
    else {
        srand(time(NULL));
        InitPeoples(peoples);
        int count = 0;
        for(int i = 0; i < POPULATION_SIZE; ++i) {
            int x = 1, y = 1;
            move_person(&peoples[i], &x, &y, maze);
            EvaluatePerson(&peoples[i], x, y);
        }
    while(count <= COUNT) {
        peoples = Crossing(peoples);
        variation(peoples);
        for(int i = 0; i < POPULATION_SIZE; ++i) {
            int x = 1, y = 1;
            move_person(&peoples[i], &x, &y, maze);
            EvaluatePerson(&peoples[i], x, y);
        }
        ++count;
    }
    time_t end = time(NULL);
    printf("used %lld(s) .\n",end - start);
    print_peoples(peoples);
    free(peoples);
    }
    return 0;
}