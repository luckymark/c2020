#include<stdio.h>
#include<math.h>
bool judge(int  n)
{
	int i;
	for(i = 2;i <= sqrt(n);i++)
		if(n % i == 0) 
			return false;
	return true;
}
int main(void)
{
	int n;
	scanf("%d", &n);
	if(judge(n))
		printf("prime");
	else
		printf("not a prime");
	return 0;
}
