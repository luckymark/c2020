
#include <stdlib.h>
#include <stdio.h>

#define MAXN 100

int notPrime[MAXN + 1] = {1, 1};

void allPrimes();

int main() {
	allPrimes();
	int pass_all = 1;
	system("title Goldbach");
	for (int i = 4; i <= MAXN; i += 2) {
		int pass_this = 0;
		for (int j = i / 2; j; j--) {
			if (!notPrime[j] && !notPrime[i - j]) {
				pass_this = 1;
				break;
			}
		}
		if(!pass_this) {
			pass_all = 0;
			break;
		}
	}
	printf("Goldbach conjecture is %s in range(%d)\n", pass_all ? "right" : "wrong", MAXN);
	system("pause");
	return 0;
}

void allPrimes() {
	for (int i = 2; i <= MAXN; i++) {
		if (!notPrime[i]) {
			for (int j = i + i; j <= MAXN; j += i) {
				notPrime[j] = 1;
			}
		}
	}
}
