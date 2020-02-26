#include<stdio.h>
#include<stdlib.h>
#include<math.h>
const int MAXN = 100;
const int max_prime = 50;
int prime[max_prime];
bool isnprime[max_prime];
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
	int i, j, count = 0;
	init(count);
	for(i = 4;i <= MAXN;i++)
	{
		for(j = 1;j <= count && prime[j] <= i / 2;j++)
		if(!isnprime[i - prime[j]])
		{
             printf("%d + %d = %d\n",prime[j], i - prime[j], i);
			 break;
		}
	}
}
