#include <stdio.h>

int main() {
	double n = 1;
	while (1) {
		double total;
		total = n / 6 + n / 12 + n / 7 + 5 + n / 2 + 4;
		if (n == total)break;
		n++;
	}
	int all=n;
	printf("%d", all);
	return 0;
}
