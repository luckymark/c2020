#include<stdio.h>
int cube(int x)
{
	return x*x*x;
}
int main()
{
	int i;
	int sum,j;
	for(i=100;i<=999;i++)
	{
		sum=0;
		j=i;
		while(j)
		{
			sum+=cube(j%10);
			j/=10;
		}
		if(sum==i)  printf("%d ",i);
	}
	return 0;
}
