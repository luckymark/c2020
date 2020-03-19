#include <stdio.h>
#include <math.h>
#include <time.h>
#define END 1000
int main() {
    clock_t start, finish;
    start = clock();
    /*version1*/
    int i, j;
    printf("2\t3\t");
    for (i = 5; i <= END; i++)
    {
        for (j = 2; j <= pow(i, 0.5); j++)
        {
            if (i % j == 0 && j != i)
            {
                j = 0;
                break;
            }
        }
        if (j != 0)
            printf("%d\t", i);
    }
/*  //version2
    int i;
    int j;
    int temp1, temp2;
    printf("2\t3\t");
    for (i = 1; (6 * i +1) <= END; i++)
    {
        temp1 = (6 * i -1);
        temp2 = (6 * i +1);
        for (j = 2; j <= pow(temp1, 0.5); j++)
        {
            if(temp1 % j == 0 && temp1 != j)
            {
                j = 0;
                break;
            }
        }
        if (j != 0)
        {
            printf("%d\t", temp1);
        }
        for (j = 2; j <= pow(temp2, 0.5); j++)
        {
            if(temp2 % j == 0 && temp2 != j)
            {
                j = 0;
                break;
            }
        }
        if (j != 0)
            printf("%d\t", temp2);
    }*/
    finish = clock();
    printf("%.3fseconds", (double)(finish - start)/CLOCKS_PER_SEC);
    return 0;
}
