#include <stdio.h>

void panduan(int num_1);

int main()
{
	int num_2;
	
	scanf("%d",&num_2);
	
	if(num_2<=1)
	{
		printf("error\n");
		printf("请重新输入："); 
		main(); 
		return 0;
	}
		
	panduan(num_2);
	
	return 0;	
}

void panduan(num_1)
{
	int i;
	for(i=2;i<num_1;++i)
	{
		if(num_1%i==0)
		{
			printf("不是素数");
			return;
		}
	}
	printf("是素数"); 
}
 
