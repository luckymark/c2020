#include<stdio.h>
#include<string.h>
const int maxn=1e2+2;
int main()
{
	int primes[maxn],is_comp[maxn],cnt=0;
	memset(is_comp,0,sizeof is_comp);
	for(int i=2;i<maxn;i++)
	{
		if(is_comp[i]==0)primes[++cnt]=i;
		for(int j=1;j<=cnt&&i*primes[j]<maxn;j++)
		{
			is_comp[i*primes[j]]=1;
			if(i%primes[j]==0)break;
		}
	}
	for(int i=4;i<=100;i+=2)
	{
		int flag=0;
		for(int p=1;p<=cnt;p++)
		{
			if(flag)break;
			for(int q=p;q<=cnt;q++)
			{
				if(primes[p]+primes[q]==i)
				{
					printf("%d+%d=%d\n",primes[p],primes[q],i);
					flag=1;
					break;
				}
				if(primes[p]+primes[q]>i)
				{
					break;
				}
			}
		}
	}
	return 0;
}
