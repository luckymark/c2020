#include<stdio.h>
#include<time.h>
#include<math.h>
void prime_first()
{	
	int text = 0;
	for (int i = 2; i < 1000000; i++) {
		int j;
		for (j = 2; j <= sqrt(i); j++)
			if (i % j == 0)
				text++;
		if (text == 0)
			printf("%d\n", i);
		text = 0;
	}
}
void prime_second()
{
	for (int i = 6; i < 1000000;i+=6)
	{
		int j;
		int text = 0;
		for (j = 2; j <= sqrt(i-1); j++)
			if ((i-1) % j == 0)
				text++;
		if (text == 0)
			printf("%d\n", i-1);
		text = 0;
		for (j = 2; j <= sqrt(i + 1); j++)
			if ((i + 1) % j == 0)
				text++;
		if (text == 0)
			printf("%d\n", i+1);
		text = 0;
	}
}
int main(void)
{
	clock_t start, finish;
	double time;
	start = clock();
	prime_first();
	finish = clock();
	time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%lf", time);
	return 0;
}