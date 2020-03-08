#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
const int MAXN = 1000;
int judge(int x)
{
    for (int i = 2; i <sqrt(x) ; ++i)
        if(x%i == 0 )
            return 1;
    return 0;
}
void getprimes(int book[],int primes[])
{
    int id = 0;
    memset(book,0, sizeof(book));
    for (int i = 2; i <=MAXN ; i++)
    {
        if(!book[i])
            primes[++id] = i;
        for (int j = 1; j<=id && primes[j]*i<=MAXN ; ++j) {
            book[primes[j] * i] = 1;
        }
    }
    for (int i = 1; i <=id ; ++i) {
        printf("%d\n",primes[i]);
    }
}

int main() {
    clock_t start,end;
    start = clock();

    int book[MAXN+5],primes[MAXN+5];
    getprimes(book,primes);

    end = clock();

    printf("All is done in %dms.",end-start);
}
