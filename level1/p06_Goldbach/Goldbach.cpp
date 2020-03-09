#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define For(x,a,b) for(x=a;x<=b;x++)
int i,i1,i2;
void Goldbach(int n);
int main(void)
{
    int m,n,i,cnt;
//    scanf("%d %d",&m,&n);              //原为验证任何一个不小于6的偶数均可表示为两个奇素数之和
	m=1;
	n=100;
    if(m<6) m=6;
    if(m%2) m++;
    cnt=0;
    for(i=m;i<=n;i+=2){
        Goldbach(i);
        cnt++;
        if(cnt%5)printf(", ");
        else printf("\n");
    }
    return 0;
}
void Goldbach(int n)
{
	int j,k,flag1,flag2,mid1,mid2;
	k=n/2;
	For(i,2,k){
		flag1=flag2=1;
		j=n-i;
		mid1=sqrt(i);
		mid2=sqrt(j);
		if(i==1||j==1)continue;
		for(i1=2;i1<=mid1;i1++){
			if(i%i1==0){
				flag1=0;
				break;
			}
		}
		For(i2,2,mid2){
			if(j%i2==0){
				flag2=0;
				break;
			}
		}
		if(flag1==1&&flag2==1){
			printf("%d=%d+%d",n,i,j);
			break;
		}
	}
}
