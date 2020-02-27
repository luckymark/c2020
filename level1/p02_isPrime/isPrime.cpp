#include<stdio.h> 
#include<math.h>
int main()
{
	int n,maxx,flag=0;
	scanf("%d",&n);
	maxx=int(sqrt(n));
	for(int i=2;i<=maxx;i++)
		if(n%i==0)
		{
			flag=1;
			break;
		}
	if(flag) printf("%d is not a prime number.",n);
	else printf("%d is a prime number.",n);
	return 0;
}
