#include<stdio.h>
#include<stdlib.h>
#define WIDTH 79


int main()
{
	int i = 0,j = 0;
	while(1)
	{
	for(i = 0;i<=WIDTH;i++)
	{
		for(j = 0;j<=i;j++)
			printf(" ");
		printf("23333");
		system("cls");
	}
	for(i = WIDTH;i>=0;i--)
	{
		for(j = i ;j>=0;j--)
			printf(" ");
		printf("23333");
		system("cls");
	}
	}
} 
