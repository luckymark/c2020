#include<stdio.h>   //∆’Õ®…∏ 
#define MAX 100

int notprime[MAX+5];

void div(int num)
{
	int i;
	for(i=2;i<=num-2;i++)
	{
		if((!notprime[i]) && (!notprime[num-i]))
		{
			printf("%d = %d + %d\n",num,i,num-i);
			return;
		}
					
	}
}
int main()
{
	int i,j;
	for(i=2;i<=MAX;i++)
	{
		j=i;
		if(!notprime[i])
			while(i+j<=MAX)
			{
				j=j+i;
				notprime[j]=1;
			}
	}
	for(i=4;i<=MAX;i+=2)
	{
		div(i);
	}
	return 0;
}
