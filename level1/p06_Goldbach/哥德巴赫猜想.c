#include <stdio.h>

int ss(int n)
{
	if(n==1)
		return 0;
	
	int i;
	for(i=2;i*i<=n;i++)
	{
		if(n%i==0)
			return 0;
	}
}
int main(void)
{
	int i,j;
	for (i=4; i<=100; i+=2)
		for (j=2; j<i; j++) {
			if (ss(j)&&ss(i-j)) {
				printf("%d=%d+%d\n",i,j,i-j);
				break;
			}
		}

return 0;
}
