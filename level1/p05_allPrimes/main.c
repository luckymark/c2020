#include <stdio.h>
#include <time.h>

int prime[200];
int n=0;

void judge(int wolka)
{
    int k;
    for (k = 0; k <= n; k++)
    {
        if (wolka % prime[k] == 0)
            return;
    }
    prime[++n] = wolka;
    return;
}

int main() {
    long start, end;
    int i;
    start = clock();
    prime[0] = 2;
    for (i = 3; i <= 1000; i++) judge(i);
    for (int j = 0; j <= n; j++)
        printf("%d\n", prime[j]);
    end = clock();
    printf("Running Time:%ldms\n", end - start);
    getchar();
    return 0;
}
