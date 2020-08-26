#include<cstdio>
int main() {
	for (int i = 5; i <= 300; i++) {
		if ((i / 6 + i / 12 + i / 7 + 9 + i / 2) == i&&0==i%6&&0==i%12&&0==i%7)
		{
			printf("%d", i);
			break;
		}
	}
	return 0;
}