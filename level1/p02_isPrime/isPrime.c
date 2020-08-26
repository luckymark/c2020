#include<stdio.h>
int main()
{
	int num,n,t;
	int a;
	printf("请输入一个正整数");
	scanf("%d",&num);
	if(num<=0){
		printf("输入不为正整数，请重新输入");
	}
	t=num;
	for(n=2;n<=t;n++){
		if(num%n==0){
			printf("%d不是素数",num);
			break;
		}
		else{
			t=num/n;
			
		}
		
		
	}
	if(n>t){
		printf("%d是素数",num);
	}
	return 0;
	
}
