#include<stdio.h>
#include<math.h>
int pow(int x)
{
	return x*x*x;
}
int main()
{
	for(int i=100;i<=999;i++)
	{
		int x=i;
		int a=i%10;
		i/=10;
		int b=i%10;
		i/=10;
		int c=i%10;
		if(pow(a)+pow(b)+pow(c)==x) 
		printf("%d\n",x);
		i=x;
	}
} 
