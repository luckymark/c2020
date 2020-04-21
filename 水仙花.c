#include <stdio.h> 
#include <math.h>
//判断出了407 
int main(){
	int x=100;
	double a,b,c;
	for(x=100;x<1000;x++){
		a=x/100;//取出百位数 
		b=x/10%10;//十位数 
		c=x%10;//个位数 
		if(x==pow(a,3)+pow(b,3)+pow(c,3)){
			printf("%d ",x);
		}
	}
	return 0;
}
