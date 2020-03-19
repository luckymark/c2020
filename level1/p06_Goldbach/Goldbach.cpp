#include<stdio.h>
const int maxnum=100;
int tot,flag=1;
int check1[maxnum+1],check2[maxnum+1],prime[maxnum+1];
int main()
{
	for(int i=2;i<=maxnum;i++)
	{
		if(!check1[i])
		{
			check1[i]=1;
			prime[++tot]=i;
		}
		for(int j=1;j<=tot;j++)
		{
			if(i*prime[j]>maxnum) break;
			check1[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
	for(int i=1;i<=tot;i++)
		for(int j=1;j<=tot;j++)
			for(int k=1;k<=tot;k++)
			{
				if(prime[i]+prime[j]+prime[k]>maxnum) break;
				check2[prime[i]+prime[j]+prime[k]]=1;
			}
	for(int i=6;i<=100;i++)
		if(!check2[i])
			flag=0;
	if(flag) printf("Goldbach conjecture can be proved when the integer is less than 100");
	else printf("Goldbach conjecture can not be proved when the integer is less than 100");
	return 0;
}
