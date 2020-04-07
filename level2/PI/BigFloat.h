#ifndef PI_BIGFLOAT_H
#define PI_BIGFLOAT_H

#define PRECISION 10000 // decimal places

/******************************************************
 It is assumed that all numbers processed are positive.
 ******************************************************/

typedef struct {
    int power; // number of digits in the integer part
    long long int digits[PRECISION + 1];
} BigFloat;

int max(int a, int b);
void initBigFloat(BigFloat *new_num, unsigned long long int num);
void printBigFloat(const BigFloat *num);

void changePower(BigFloat *num, int new_power);
int alignPower(BigFloat *num1, BigFloat *num2);
int equalZero(const BigFloat *num);
int lessThanOne(const BigFloat *num);
int removeZeroes(BigFloat *num);
void copyBigFloat(BigFloat *dest, const BigFloat *src);
int compareBigFloat(const BigFloat *num1, const BigFloat *num2);

void addBigFloat(const BigFloat *num1, const BigFloat *num2, BigFloat *res);
void subBigFloat(const BigFloat *num1, const BigFloat *num2, BigFloat *res);
void mulBigFloatAndInt(const BigFloat *big_float, int num, BigFloat *res);
void mulBigFloat(const BigFloat *num1, const BigFloat *num2, BigFloat *res);
void divBigFloat(const BigFloat *num1, const BigFloat *num2, BigFloat *res);

void factorial(int num, BigFloat *res);
void doubleFactorialOdd(int num, BigFloat *res);

#endif //PI_BIGFLOAT_H
