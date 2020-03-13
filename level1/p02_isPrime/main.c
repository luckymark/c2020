#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int isPrime(long long n);

int main() {
	system("title isPrime");
	printf("Positive Integer N = ");
	long long n;
	scanf("%lld", &n);
	printf("%lld %s a Prime Number\n", n, isPrime(n) ? " I S " : "ISN'T");
	system("pause");
	return 0;
}

int isPrime(long long n) {
	if (n == 1 || (n != 2 && n % 2 == 0)) return 0;
	long long sqrt_n = (long long)sqrt(n);
	for (long long i = 3; i < sqrt_n; i += 2) {
		if (n % i == 0) return 0;
	}
	return 1;
}
