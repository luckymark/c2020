#include <stdio.h>
#include <math.h>
int main(){
	int x=100;
	double a,b,c;
	for(x=100;x<1000;x++){
		a=x/100;
		b=x/10%10;
		c=x%10;
		if(x==pow(a,3)+pow(b,3)+pow(c,3)){
			printf("%d ",x);
		}
	}
	return 0;
}
