#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    int i, j, k;
    for (i = 1; i < 10; i++)
        for (j = 0; j < 10; j++)
            for (k = 0; k < 10; k++)
                if (i * 100 + j * 10 + k == pow(i, 3) + pow(k, 3) + pow(j, 3))//
                    printf("%d%d%d ", i, j, k);
   return 0;
}