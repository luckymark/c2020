#include <stdio.h>
#include <math.h>

int main()
{
    int Isprime(int n);
    int i, j, flag;
    for (i = 6; i <= 100; i = i + 2)
    {
        flag = 0;
        for (j = 3; j <= i / 2; j += 2)
        {
            if (Isprime(j) && Isprime(i - j))
            {
                flag = 1;
                printf("%d = %d +%d\n", i, j, i - j);
                break;
            }
        }
        if (flag == 0) break;
    }
    if (i == 102) printf("哥德巴赫猜想正确！\n");
    else printf("哥德巴赫猜想不成立！\n");
    getchar();
    return 0;
}
int Isprime(int n)
{
    int k;
    for (k = 2; k <= sqrt(n); k ++)
    {
        if (n % k == 0) break;
    }
    if (k == (int)sqrt(n) + 1) return 1;
    else return 0;
}