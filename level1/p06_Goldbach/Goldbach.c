#include<stdio.h>
int Primes(int a);
int main()
{
	int n,m;
	for(n=4;n<=100;n=n+2){
		for (m=2;m<=n/2;m++){
			
			if(Primes(m)==m){
			
				if(Primes(n-m)==n-m){
				printf("%d=%d+%d    ",n,m,n-m);
				break;
			}
			}
		}
	}
	return 0;
}


int Primes(int a)
{
	int t;
	for(t=2;t<=a;t++){
		if(a%t==0){
			break;
		}
	}
	if(t==a){
		return a;
	}
}
