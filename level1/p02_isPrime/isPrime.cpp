#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define For(x,a,b) for(x=a;x<=b;x++)
int i,i1,i2;
int main(void)
{
	int number,mid1,flag;
	scanf("%d",&number);
	mid1=sqrt(1.0*number)+1;
	flag=0;
	if(number<=1){
		printf("Error");
		exit(0);
	}
	if(number==2)
	{
		printf("Yes.");
		exit(0);
	}
	For(i,2,mid1){
		if(number%i==0){
			flag=1;
			break;
			}
		}
	if(flag==0){
		printf("Yes.");
		}else{
		printf("No.");	
			}
	return 0;
	system("pause");
	return 0;
}
