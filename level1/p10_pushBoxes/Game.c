//
// Created by pointkab on 2020/3/10.
//
#include <stdio.h>
#include "Game.h"
void ShowMap(int *a, int N, int M)
{
    int i, j, temp;
    for (i = 0; i < N; i++)
    {
        for (j = 0;j < M; j++)
        {
            temp = *(a + (i * N) + j);
            switch (temp)
            {
                case 1:
                    printf("#");
                    break;
                case 2:
                    printf("■");
                    break;
                case 0:
                    printf(" ");
                    break;
                case -1:
                    printf("□");
                    break;
            }
        }
    }
}
