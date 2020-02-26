#include <stdio.h>
#include <stdlib.h>

int main() {
	long long n;
	int isPrime = 1;
	system("title isPrime");
	printf("Positive Integer N = ");
	scanf("%lld", &n);
	if (n == 1 || n != 2 && n % 2 == 0) isPrime = 0;
	else
		for (long long i = 3; i < n / 2; i += 2)
			if (n % i == 0) {
				isPrime = 0;
				break;
			}
	printf("%lld %s a Prime Number\n", n, isPrime ? "IS" : "ISN'T");
	system("pause");
	return 0;
}
