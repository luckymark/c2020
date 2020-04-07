#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigFloat.h"

inline int max(int a, int b) {
    return a > b ? a : b;
}

void initBigFloat(BigFloat *new_num, unsigned long long int num) {
    memset(new_num->digits, 0, sizeof(long long int) * (PRECISION + 1));
    int length = 0;
    long long int *digits = (long long int*)malloc(sizeof(long long int) * (PRECISION + 1));
    while (num) {
        digits[length] = (long long int)(num % 10);
        num = num / 10;
        length++;
    }
    memcpy(new_num->digits + PRECISION - length + 1, digits, sizeof(long long int) * length);
    new_num->power = length;
    free(digits);
}

void printBigFloat(const BigFloat *num) {
    for (int i = 0; i <= PRECISION; i++) {
        if (i == num->power) {
            printf(".");
        }
        printf("%llu", num->digits[PRECISION - i]);
    }
    printf("\n");
}

void changePower(BigFloat *num, int new_power) {
    if (new_power > num->power || !(num->digits[PRECISION])) {
        BigFloat temp;
        initBigFloat(&temp, 0);
        int change = new_power - num->power;
        if (change > 0) {
            memcpy(temp.digits, num->digits + new_power - num->power,
                   sizeof(long long int) * (PRECISION + 1 - change));
        } else if (change < 0) {
            memcpy(temp.digits - change, num->digits,
                   sizeof(long long int) * (PRECISION + 1 + change));
        }
        memcpy(num->digits, temp.digits, sizeof(long long int) * (PRECISION + 1));
        num->power = new_power;
    }
}

int alignPower(BigFloat *num1, BigFloat *num2) {
    int new_power = max(num1->power, num2->power);
    if (num1->power != num2->power) {
        changePower(num1, new_power);
        changePower(num2, new_power);
    }
    return new_power;
}

int equalZero(const BigFloat *num) {
    for (int i = 0; i <= PRECISION; i++) {
        if (num->digits[i]) {
            return 0;
        }
    }
    return 1;
}

int removeZeroes(BigFloat *num) {
    BigFloat one;
    initBigFloat(&one, 1);
    int zeroes = 0;
    for (int i = PRECISION; i > PRECISION - num->power; i--) {
        if (num->digits[i] || num->power - zeroes == 1) {
            break;
        }
        zeroes++;
    }
    changePower(num, num->power - zeroes);
    return zeroes;
}

void copyBigFloat(BigFloat *dest, const BigFloat *src) {
    dest->power = src->power;
    memcpy(dest->digits, src->digits, sizeof(long long int) * (PRECISION + 1));
}

int compareBigFloat(const BigFloat *num1, const BigFloat *num2) {
    BigFloat left, right;
    copyBigFloat(&left, num1);
    copyBigFloat(&right, num2);
    if (!left.digits[PRECISION]) {
        removeZeroes(&left);
    }
    if (!right.digits[PRECISION]) {
        removeZeroes(&right);
    }
    if (left.power != right.power) {
        return left.power > right.power ? 1 : -1;
    }
    for (int i = PRECISION; i >= 0; i--) {
        if (left.digits[i] > right.digits[i]) {
            return 1;
        } else if (left.digits[i] < right.digits[i]) {
            return -1;
        }
    }
    return 0;
}

void addBigFloat(const BigFloat *num1, const BigFloat *num2, BigFloat *res) {
    BigFloat left, right;
    copyBigFloat(&left, num1);
    copyBigFloat(&right, num2);
    initBigFloat(res, 0);
    res->power = alignPower(&left, &right);
    for (int i = 0; i < PRECISION; i++) {
        res->digits[i] += left.digits[i] + right.digits[i];
        if (res->digits[i] > 9) {
            res->digits[i] -= 10;
            res->digits[i + 1]++;
        }
    }
    res->digits[PRECISION] += left.digits[PRECISION] + right.digits[PRECISION];
    if (res->digits[PRECISION] > 9) {
        changePower(res, res->power + 1);
        res->digits[PRECISION - 1] -= 10;
        res->digits[PRECISION]++;
    }
}

void subBigFloat(const BigFloat *num1, const BigFloat *num2, BigFloat *res) {
    if (compareBigFloat(num1, num2) == 1) {
        BigFloat left, right;
        copyBigFloat(&left, num1);
        copyBigFloat(&right, num2);
        initBigFloat(res, 0);
        res->power = alignPower(&left, &right);
        for (int i = 0; i < PRECISION; i++) {
            res->digits[i] += left.digits[i] - right.digits[i];
            if (res->digits[i] < 0) {
                res->digits[i] += 10;
                res->digits[i + 1]--;
            }
        }
        res->digits[PRECISION] += left.digits[PRECISION] - right.digits[PRECISION];
        removeZeroes(res);
    } else {
        initBigFloat(res, 0);
    }
}

void mulBigFloatAndInt(const BigFloat *big_float, int num, BigFloat *res) {
    BigFloat big;
    copyBigFloat(&big, big_float);
    initBigFloat(res, 0);
    res->power = big.power;
    for (int i = 0; i <= PRECISION; i++) {
        res->digits[i] += big.digits[i] * num;
    }
    for (int i = 0; i < PRECISION; i++) {
        if (res->digits[i] > 9) {
            res->digits[i + 1] += res->digits[i] / 10;
            res->digits[i] %= 10;
        }
    }
    while (res->digits[PRECISION] > 9) {
        changePower(res, res->power + 1);
        res->digits[PRECISION] += res->digits[PRECISION - 1] / 10;
        res->digits[PRECISION - 1] %= 10;
    }
}

void mulBigFloat(const BigFloat *num1, const BigFloat *num2, BigFloat *res) {
    BigFloat left, right, temp;
    copyBigFloat(&left, num1);
    copyBigFloat(&right, num2);
    initBigFloat(res, 0);
    for (int i = 0; i <= PRECISION; i++) {
        mulBigFloatAndInt(&left, right.digits[i], &temp);
        temp.power += i + right.power - PRECISION - 1;
        addBigFloat(res, &temp, res);
    }
}

void divBigFloat(const BigFloat *num1, const BigFloat *num2, BigFloat *res) {
    BigFloat left, right;
    copyBigFloat(&left, num1);
    copyBigFloat(&right, num2);
    initBigFloat(res, 0);
    res->power = 1;
    for (int i = PRECISION; i >= 0; i--) {
        while (compareBigFloat(&left, &right) == 1) {
            subBigFloat(&left, &right, &left);
            res->digits[i]++;
        }
        if (equalZero(&left)) {
            break;
        }
        left.power++;
    }
}

void factorial(int num, BigFloat *res) {
    initBigFloat(res, 1);
    for (int i = 2; i <= num; i++) {
        mulBigFloatAndInt(res, i, res);
    }
}

void doubleFactorialOdd(int num, BigFloat *res) {
    initBigFloat(res, 1);
    for (int i = 3; i <= num; i += 2) {
        mulBigFloatAndInt(res, i, res);
    }
}
