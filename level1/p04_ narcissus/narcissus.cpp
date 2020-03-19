#include<stdio.h>
int main() 
{
	for(int i=100;i<1000;i++)
	{
		int n1=i%10,n2=i/10%10,n3=i/100;
		if(n1*n1*n1+n2*n2*n2+n3*n3*n3==i) printf("%d\n",i);
	}
	return 0;
}
