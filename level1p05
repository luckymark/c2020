#include<stdio.h>
#include<string.h>
const int maxn=1e3+2;
void fastprint(int x)
{
	if(x==0)
		return;
	fastprint(x/10);
	printf("%d",x%10);
	return;
}
int main()
{
	int primes[maxn],is_comp[maxn],cnt=0;
	for(int i=2;i<maxn;i++)
	{
		if(!is_comp[i])primes[++cnt]=i;
		for(int j=1;j<=cnt&&i*primes[j]<maxn;j++)
		{
			is_comp[i*primes[j]]=1;
			if(i%primes[j]==0)break;
		}
	}
	puts("All primes less than 1e3 are:");
	for(int i=1;i<=cnt;i++)fastprint(primes[i]),puts("");
}
