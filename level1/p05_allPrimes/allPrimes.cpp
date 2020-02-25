#include<stdio.h>
#include<time.h>

int prime[400];
bool isnprime[1001];
int cnt = 0;
void init(int maxn)
{
	int i, j;
	for(i = 2;i <= maxn;i++)
	{
		if(!isnprime[i]) prime[++cnt] = i;
		for(j = 1;j <= cnt && i * prime[j] <= maxn;j++)
		{
			isnprime[i * prime[j]] = true;
			if(i % prime[j] == 0) break;
		}
	}
}
int main(void)
{
	double a, b;
	int i;
	
	a = (double)clock();
	
	init(1000);
	
	for(i = 1;i <= cnt;i++)
	printf("%d\n", prime[i]);
	
	b = (double)clock();
	printf("total time:%lf s", (b - a)/CLOCKS_PER_SEC);
	return 0;
}
