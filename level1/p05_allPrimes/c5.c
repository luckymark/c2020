#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH 1000
int isPrime(int number) {
    for (int i = 2; i * i <= number; i++)
        if (number % i == 0)return 0;
    return 1;
}
int main(void)
{
    long      i = 10000000L;
    clock_t start, finish;
    double    duration;
    start = clock();
    for (int i = 2; i < LENGTH; i++)
    {
        if (isPrime(i))printf("%d ", i);

    }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%f seconds/n", duration);
    system("pause");
}

