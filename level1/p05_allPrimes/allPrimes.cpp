#include<stdio.h>
#include<time.h>
#include<string.h> 
const int MAXN = 1000;
const int MAX_prime = 400;
int prime[MAX_prime];
bool isnprime[MAXN];
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
	
	memset(isnprime,false,sizeof(isnprime));
	
	a = (double)clock();
	
	init(MAXN);
	
	for(i = 1;i <= cnt;i++)
	printf("%d\n", prime[i]);
	
	b = (double)clock();
	printf("total time:%lf s", (b - a)/CLOCKS_PER_SEC);
	return 0;
}
