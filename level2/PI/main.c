/**********************
 This calculation use the following formula:
 pi/2 = 1 + 1/3 + 1*2/3*5 + 1*2*3/3*5*7 + ... + n!/(2n+1)!!
 **********************/

#include <stdio.h>
#include "BigFloat.h"

int main(void) {
    int items = 500; // more items, higher accuracy.
    BigFloat res, numerator, denominator, item;
    initBigFloat(&res, 1);

    for (int n = 1; n <= items; n++) {
        printf("%d\n", n);
        factorial(n, &numerator);
        doubleFactorialOdd(2 * n + 1, &denominator);
        divBigFloat(&numerator, &denominator, &item);
        addBigFloat(&res, &item, &res);
    }
    mulBigFloatAndInt(&res, 2, &res);
    printBigFloat(&res);

    return 0;
}
