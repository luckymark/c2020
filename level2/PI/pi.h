//
// Created by tungsten on 2020/3/1.
//

#ifndef PI_PI_H
#define PI_PI_H

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<math.h>
#include<string.h>

#define ACCURACY 21000
//decimal part length
//real accuracy is log10(MOD)*ACCURACY
#define SHOWLEN 800
//print length
#define MAX(a,b) a>b?a:b
//macro func
#define MOD 10000
//compressing status to reduce memory and time cost
#define FILENAME "pi.txt"

struct BigNum{
    int power;
    int digit[ACCURACY+1];
};
void bigAdd(struct BigNum* numA,struct BigNum* numB,struct BigNum *numRes);
// a+b
void bigSub(struct BigNum* numA,struct BigNum* numB,struct BigNum *numRes);
// a-b
void bigDiv(struct BigNum* numA,int numB,struct BigNum* numRes);
// a/b b is a normal number
void changePower(struct BigNum* num,int target);
// change power into target
void printNum(struct BigNum* num);
void savePi(struct BigNum* num);
struct BigNum* getBigNum(int num);

#endif //PI_PI_H
