#include<stdio.h>
#include<math.h>
#define RANGE 100

int main(void)
{
	//init
	int i = 1,j = 0;
	int book[RANGE + 1] = {0};
	
	//创建RANGE以内的素数表
	book[0] = 1;
	book[1] = 1;
	for(i = 1; i<= sqrt(RANGE);i++)
	{
		if(1 == book[i])
			continue;
		j = i * i;
		while(j <= RANGE)
		{
			book[j] = 1;
			j += i;
		}
	}
	
	//逐个验证
	for(i = 2;i<= RANGE;i+=2)
		for(j = 1;j<= i/2;j++)
		{
			if(1 == book[j])
				continue;
			if(0 == book[i-j])
				printf("%d = %d + %d\n",i,j,i-j);
		}

	getchar();		
	return 0;
	 
}
