#include<stdio.h>
int main()
{
	puts("All three digit narcissistic number are:");
	for(int i=100;i<=999;i++)
	{
		int tot=0,tmp=i;
		for(int j=1;j<=3;j++)
		{
			int u=tmp%10;
			tot+=u*u*u;
			tmp/=10;
		}
		if(tot==i)printf("%d\n",i);
	}
}
