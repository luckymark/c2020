#include<stdio.h>
#include<math.h>
bool judge_fermat(int n)
{
	if(n == 2) return true;
	int x = 1, y = 2, z = n - 1;
	while(z)
	{
		if(z & 1)
		x = x * y % n;
		z >>= 1;
		y = y * y % n;
	}
	if(x % n ==1)
	return true;
	return false;
}
int p[7]= {2, 3, 5, 6, 11, 13, 17};
int pw(int b, int n,int p)
{
	long long x = 1, y = b;
	while(n)
	{
		if(n & 1)
		x = x * y %p;
		y = y * y % p;
		n >>= 1;
	}
	return x % p; 
 } 
bool miller_rabin(int n, int p)
{
	int z = n - 1;
	if(n == p) return true;
	while(true)
	{
		int ans = pw(p, z, n);
		if(ans == n - 1)
		return true;
		else if(ans != 1) return false;
		if(z & 1) return true;
		z >>= 1;
	}
}
bool judge_miller_rabin(int n)
{
	int  i;
	for(i = 0;i < 7;i++)
	if(!miller_rabin(n, p[i])) return false;
	return true;
}
bool judge(int  n)
{
	int i;
	for(i = 2;i <= sqrt(n);i++)
	if(n % i == 0) return false;
	return true;
}
int main(void)
{
	int n;
	scanf("%d", &n);
//	if(judge_fermat(n))
//	if(judge_miller_rabin(n))
	if(judge(n))
	printf("prime");
	else
	printf("not a prime");
	return 0;
}
