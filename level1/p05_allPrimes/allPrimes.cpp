#include<stdio.h>
#include<time.h>
const int maxnum=1000;
int tot;
int check[maxnum+1],prime[maxnum+1];
double t1,t2;
int main()
{
	t1=clock();
	for(int i=2;i<=maxnum;i++)
	{
		if(!check[i])
		{
			check[i]=1;
			prime[++tot]=i;
		}
		for(int j=1;j<=tot;j++)
		{
			if(i*prime[j]>maxnum) break;
			check[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
	printf("All prime numbers between 2 and 1000:\n");
	for(int i=1;i<=tot;i++) printf("%d\n",prime[i]);
	t2=clock();
	printf("Time used=%.2lf\n",(t2-t1)/CLOCKS_PER_SEC);
	return 0;
}
