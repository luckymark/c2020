#include<stdio.h>
#include<math.h>
int main()
{
	int a;
	scanf("%d",&a);
	for(int i=2;i<=sqrt(a);i++)
	if(a%i==0)
	{
		printf("%d is not a prime number",a);
		return 0;
	}	
	printf("%d is a prime number",a);
	return 0;
} 
