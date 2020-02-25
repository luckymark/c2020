#include<stdio.h>
bool judge(int n)
{
	int x = 0, y = n;
	while(n)
	{
		int z = n % 10;
		x += z * z * z;
		n /=10;
	}
	return y==x;
}

int main(void)
{
	int i;
	for(i = 100;i <= 999;i++)
	if(judge(i))
	printf("%d ", i);
	return 0;
}
