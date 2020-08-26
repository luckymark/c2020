#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#define f(i,j,k) for(i=(j);i<=(k);i++)
const int maxn = 10000; int i;
bool isprime(int x) {
	bool a[maxn + 5];
	memset(a, true, sizeof(a));
	f(i, 2, sqrt(maxn))
	{
		if (a[i]) {
			for (int y = 1; i + y * i <= maxn; y++)
				a[i + y * i] = false;
		}
	}
	if (a[x]) return 1;
	else return 0;
}
int main() {
	int n;
	scanf_s("%d", &n);
	if (isprime(n)) {
		puts("n is a prime");
	}
	else puts("n is not a prime");
	return 0;
}