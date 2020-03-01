#include<stdio.h>
#define maxn 1e7
int main()
{
	puts("Please input a integer n less equal than 1e7");
	int n,is_prime;
	while(scanf("%d",&n)==1)
	{
		if(n>maxn||n<=0)
		{
			puts("Input out of limit.");
			continue;
		}
		if(n==1)
		{
			puts("n is neither prime number nor composite number.");
			continue;
		}
		is_prime=0;
		for(int i=2;i*i<=n;i++)
		{
			if(n%i==0)
			{
				is_prime=1;
				break;
			}
		} 
		if(!is_prime)puts("n is a prime number.");
		else puts("n isn't a prime number.");
	}
	return 0;
}
