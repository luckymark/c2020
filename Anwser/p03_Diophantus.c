#include<stdio.h>
int main()
{
	int i,ans,m;
	for(i=1;i<=120;i++)
	{
		if(i%12==0  &&  i%7==0)
		{
			m=i-(i/6)-(i/12)-(i/7)-(i/2);
			if(m==9)  ans=i;
		}
	}
	printf("%d\n",ans);
	return 0;
} 
