#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define For(x,a,b) for(x=a;x<=b;x++)
int i,i1,i2;
void hanoi(int n,char a,char b,char c);
int main(void)
{
	int n;
	printf("Please input the number of the disk:\n");
	scanf("%d",&n);
	hanoi(n,'a','b','c');
	return 0;
}
void hanoi(int n,char a,char b,char c)
{
	if(n==1)printf("%c --> %c\n",a,b);
	else{
		hanoi(n-1,a,c,b);
		printf("%c --> %c\n",a,b);
		hanoi(n-1,c,b,a);
	}
}
