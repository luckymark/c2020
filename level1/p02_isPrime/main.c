#include <stdio.h>
#include <math.h>
int main() {
    long N;
    scanf("%ld",&N);
    long i;
    if (N == 1)
    {
        printf("%ld不是素数", N);
        return 0;
    }
    for (i = 2; i <= pow(N, 0.5); i++)
    {
        if ((N % i == 0 && N != i) || N == 4)
        {
            printf("%ld不是素数", N);
            return 0;
        }
    }
    printf("%ld是素数", N);
    return 0;
}
