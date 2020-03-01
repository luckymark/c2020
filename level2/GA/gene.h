//
// Created by tungsten on 2020/2/29.
//

#ifndef GA_GENE_H
#define GA_GENE_H

#include<stdio.h>
#include<limits.h>
#include<conio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


#define MAXN 10
#define PATHLEN 25
//need to change


#define MAXWAIT 5
#define FREQ 2000
#define POOLSIZE 1000
#define EPOCHSIZE 200000
#define CHOOSERATE 0.8
#define MUTARATE 0.05
#define LAMBDA 10

int resIdx=-1;
int begX,begY;
int endX,endY;
int epoch=0;
int best;
//循环数组
FILE* fp;
char map[MAXN][MAXN];
struct Gene{
    float mark;
    bool code[PATHLEN][2];
    int count;
    bool reach;
};
float prob[POOLSIZE];
struct Gene population[3][POOLSIZE];

inline float randFloat(){
    return ((float)(rand()%30001))/30000;
}
float setMark(struct Gene* ptr);
void setProb();
void mutate();
void exchange();
void readMap(char* filename);
void initPopulation(unsigned seed);
void evalution();
void printMap();
void printAns();

#endif //GA_GENE_H
