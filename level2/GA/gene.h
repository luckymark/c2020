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
//map size
#define PATHLEN 25
//path\gene length

//need to change


#define MAXWAIT 5
//经过多少次找到相同解，就视为最优解
#define POOLSIZE 1000
//population pool
#define EPOCHSIZE 200000
//epoch times
#define CHOOSERATE 0.8
//优势种群阈值
#define MUTARATE 0.05
//变异率
#define LAMBDA 10
//路径长度惩罚系数

int resIdx=-1;
//最优基因下标

int begX,begY;
int endX,endY;
int epoch=0;
int best=INT_MAX;
//best_length
FILE* fp;
char map[MAXN][MAXN];
struct Gene{
    int mark;
    bool code[PATHLEN][2];
    int count;
    bool reach;
};
float prob[POOLSIZE];
//prefix sum of prob

struct Gene population[3][POOLSIZE];
//循环数组
//0，1轮流为父种群和子种群，2为优势种群

inline float randFloat(){
    return ((float)(rand()%30001))/30000;
}
int setMark(struct Gene* ptr);
void setProb();
void mutate();
void exchange();
void readMap(char* filename);
void initPopulation(unsigned seed);
void evalution();
void printMap();
void printAns();
void emulate(struct Gene* ptr,int *x,int *y,int *count,bool res);

#endif //GA_GENE_H
