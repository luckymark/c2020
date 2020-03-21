#include <time.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long counter = 0;

void move(int n, char a, char b, char c) {
	counter++;
	if (n == 1) {
		printf(" %c2%c", a, c);
	}
	else {
		move(n - 1, a, c, b);
		printf(" %c2%c", a, c);
		move(n - 1, b, a, c);
	}
}

int main() {
	system("title hanoi");
	printf("How many? ");
	int n;
	scanf("%d", &n);
	clock_t t0 = clock();
	move(n, 'a', 'b', 'c');
	printf("\nTotal steps (2^n-1) = %I64u", counter); // %I64u -> %llu in Linux/Mac
	printf("\nTime cost with echo = %fs\n", (double)(clock() - t0) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}
