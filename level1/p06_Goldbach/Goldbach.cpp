#include<stdio.h>
#include<cmath>

int Prime_tol,Prime[100];
bool isPrime[100];

void pre()
{
	for(int i=2;i<=100;i++)
	{
		int jud=1;
		for(int j=2;j<=sqrt(i);j++)
		{
			if(i%j==0) 
			{
				jud=0;
				break;
			}
		}
		if(jud)
		{
			Prime_tol++;
			Prime[Prime_tol]=i;
			isPrime[i]=1;
		}
	}
}
void search(int x)
{
	for(int i=1;i<=Prime_tol&&Prime[i]<x;i++)
	{
		int y=x-Prime[i];
		if(isPrime[y])
		{
			printf("%d is equals to %d + %d\n",x,y,Prime[i]);
			return;
		}
	}
	printf("couldn't find an equation.");
}
int main()
{
	pre();
	for(int i=4;i<=100;i+=2)
	search(i);
}
