#include<stdio.h>
#include<stdlib.h>
#define WIDTH 79
 
int main()
{
	int i = 0,j = 0;
	while(1)
	{
		for(i = 0;i<=2 * WIDTH;i++)
		{
			for(j = 0;j<=WIDTH - abs(i - WIDTH);j++)
				printf(" ");
			printf("23333");
			system("cls");
		}
	}
	return 0;
} 
