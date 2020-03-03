#include<stdio.h>   //∆’Õ®…∏ 
#include<time.h> 
int notprime[1010];
int main()
{
	int i,j;
	clock_t start,end;
	start=clock();
	for(i=2;i<=1000;i++)
	{
		j=i;
		if(!notprime[i])
			while(i+j<=1000)
			{
				j=j+i;
				notprime[j]=1;
			}
	}
	for(i=2;i<=1000;i++)
	{
		if(!notprime[i])  printf("%d ",i);
	}
	printf("\n");
	end=clock();
	double duration=(double)(end-start);
	printf("You use %lf ms to execute this code.",duration);
	return 0;
}
