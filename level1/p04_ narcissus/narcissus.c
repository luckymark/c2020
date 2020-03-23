#include<stdio.h>
int main()
{
	int n;
	int a,b,c;
	int sum;
	printf("3位水仙花数有：");
	for(n=100;n<=999;n++){
		a=n/100;
		b=n/10-10*a;
		c=n-a*100-b*10;
		sum=a*a*a+b*b*b+c*c*c;
		if(sum==n){
			printf("%d ",n);
		}
		
	}
	return 0;
}
