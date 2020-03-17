#include <stdio.h>
#include <math.h>
int isPrime(int number) {
    for (int i = 2; i * i <= number; i++)
        if (number % i == 0)return 0;
    return 1;
}
int main()
{
	int n;
	scanf_s("%d", &n);

    if (isPrime(n)) {
        printf("是素数\n");
    }
    else{
        printf("不是素数\n");
    };
	return 0;
}