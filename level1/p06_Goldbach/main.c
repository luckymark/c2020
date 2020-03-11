#include <stdio.h>
/*Goldbach:任一大于2的偶数，都可表示成两个素数之和*/
int main() {
    int Nums[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    int i, j, k, index = -1;
    for (i = 4; i < 101; i+=2)
    {
        for (j = 0; j < 25; j++)
        {
            for (k = 0; k < 25; k++)
            {
                if ((i - Nums[j]) == Nums[k])
                {
                    index = 1;
                    break;
                }
                if (j == 24 && k == 24)
                {
                    index = 0;
                }
                if (index == 0 || index == 1)
                    break;
            }
            if (index == 0 || index == 1)
                break;
        }
        if (index == 0 || index == 1)
            break;
    }
    if (index == 0)
    {
        printf("It is wrong!");
    } else{
        printf("It is true!");
    }

    return 0;
}
