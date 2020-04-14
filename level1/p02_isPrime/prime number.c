#include<stdio.h>

int main()

{
	int a;
	scanf("%d",&a);
	
	if(a==1){
		printf("NO");
		return 0;
	}	
	
	int i;for(i=2;i*i<=a;i++)
	{
		if(a%i==0)	printf("NO");
		return 0;
	}
	printf("YES");
	return 0;
}
