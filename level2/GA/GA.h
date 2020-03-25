//
// Created by surfaceCS on 2020/3/25.
//

#ifndef GA_GA_H
#define GA_GA_H

#define GENELENGTH 10000
#define PLAYERSNUMBER 10000
#define WIDTH 10
#define HEIGHT 10
#define EVOLUTION 1000

typedef struct player{
    int x;
    int y;
    int adapt;
    int gene[GENELENGTH];
}player;

typedef struct greatest{
    int num;
    int adapt;
    int steps;
}greatest;

typedef struct start{
    int x;
    int y;
}start;

typedef struct end{
    int x;
    int y;
}end;

void initial(void);
void readinmap(void);
void printmap(void);
void evolution(void);
void judgethegreat(void);
void printroad(void);

#endif //GA_GA_H
