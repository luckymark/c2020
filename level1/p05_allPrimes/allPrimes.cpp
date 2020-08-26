#include<stdio.h>
#include<time.h>
#include<string.h> 
const int MAXN = 1000;
const int MAXPRIME = 400;
int prime[MAXPRIME];
bool isnprime[MAXN];

void init(int &count)
{
	int i, j;
	for(i = 2;i <= MAXN;i++)
	{
		if(!isnprime[i]) prime[++count] = i;
		for(j = 1;j <= count && i * prime[j] <= MAXN;j++)
		{
			isnprime[i * prime[j]] = true;
			if(i % prime[j] == 0) break;
			
		}
	}
}
int main(void)
{
	double a, b;
	int i, count = 0;
	a = (double)clock();
	
	memset(isnprime,false,sizeof(isnprime));
	
	init(count);
	
	for(i = 1;i <= count;i++)
		printf("%d\n", prime[i]);
	
	b = (double)clock();
	printf("total time:%lf s", (b - a)/CLOCKS_PER_SEC);
	return 0;
}
