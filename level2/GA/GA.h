//
// Created by surfaceCS on 2020/3/25.
//

#ifndef GA_GA_H
#define GA_GA_H

#define GENELENGTH 100
#define PLAYERSNUMBER 1000
#define WIDTH 20
#define HEIGHT 20
#define EVOLUTION 20
#define FATHER 60

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
