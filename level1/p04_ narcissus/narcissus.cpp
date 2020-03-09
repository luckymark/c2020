#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define For(x,a,b) for(x=a;x<=b;x++)
int i,i1,i2;
int main(void)
{
	int n,x,tmin,tmax,mid1,mid2,mid3,sum,flag;
	tmin=tmax=flag=1;
//	scanf("%d",&n);     //原为计算n位水仙花数 
	n=3;                //改为计算3位水仙花数 
	for(i=1;i<n;i++){
		tmin=tmin*10;
	}
	tmax=tmin*10-1;
	For(x,tmin,tmax){
		mid1=mid2=x;
		sum=0;
		For(i1,1,n){
			mid1=mid2%10;
			mid2=mid2/10;
			for(i2=mid3=1;i2<=n;i2++){
				mid3=mid3*mid1;
			}
			sum=sum+mid3;
		}
		if(sum==x){
			if(flag>1)printf("\n");
			printf("%d",x);
			flag++;
		}
	}
	return 0;
	system("pause");
	return 0;
}
