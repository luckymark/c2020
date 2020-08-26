#include<stdio.h>
const int minn = 100;
const int maxn = 999;
const int a = 3;
int pw(int a, int b)
{
	int ans = 1, t = a;
	while(b)
	{
		if(b & 1) 
			ans *= t;
		t = t * t;
		b >>= 1;
	}
	return ans;
}
bool judge(int n)
{
	int x = 0, y = n;
	while(n)
	{
		int z = n % 10;
		x += pw(z, a);
		n /=10;
	}
	return y==x;
}

int main(void)
{
	int i;
	for(i = minn;i <= maxn;i++)
		if(judge(i))
			printf("%d ", i);
	return 0;
}
