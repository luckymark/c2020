#include<cstdio>
int main() {
	int a, b, c;
	for (int i = 100; i < 1000; i++) {
		a = i % 10;
		b = (i % 100) / 10;
		c = i / 100;
		if ((a * a * a + b * b * b + c * c * c) == i) printf("%d ",i);
	}
	return 0;
}