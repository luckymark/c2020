#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAXN 1000

void allPrimes(int echo);

int main() {
	system("title allPrimes");
	clock_t t0 = clock();
	allPrimes(1);
	printf("\nTime cost (with echo on ) = %fs"  , (double)(clock() - t0) / CLOCKS_PER_SEC);
	t0 = clock();
	allPrimes(0);
	printf("\nTime cost (with echo off) = %fs\n", (double)(clock() - t0) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}

void allPrimes(int echo) {
	int book[MAXN + 1] = {0};
	for (int i = 2; i <= MAXN; i++) {
		if (!book[i]) {
			if(echo) {
				printf("%5d", i);
			}
			for (int j = i + i; j <= MAXN; j += i) {
				book[j] = 1;
			}
		}
	}
}
