#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define For(x,a,b) for(x=a;x<=b;x++)
int i,i1,i2;
int main(void)
{
	int prime[865];
	int flag;
	double duration;
	clock_t start,finish;
	prime[0]=2;
	i2=0;
	start=clock();
	For(i,3,1000){
		flag=1;
		For(i1,0,i2){
			if(i%prime[i1]==0){
				flag=0;
				break;
			}
		}
		if(flag==1){
			i2++;
			prime[i2]=i;
		}
	}
	For(i,0,i2){
		printf("%4d",prime[i]);
		if((i+1)%10==0)printf("\n");
		else printf(" ");
	}                   //Êä³öÅÅ°æ 
	printf("\n");
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf( "It costs %f seconds.", duration);
	return 0;
}
