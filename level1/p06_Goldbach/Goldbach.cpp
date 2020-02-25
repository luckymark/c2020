#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int prime[200];
bool isnprime[200];
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
	int i, j;
	init(100);
	for(i = 4;i <= 100;i++)
	{
		for(j = 1;j <= cnt && prime[j] <= i / 2;j++)
		if(!isnprime[i - prime[j]])
		{
             printf("%d + %d = %d\n",prime[j], i - prime[j], i);
			 break;
		}
	}
}
