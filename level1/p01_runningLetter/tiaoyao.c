#include<stdio.h> 
#include<stdlib.h>
int main()
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=1;j<=i;j++)
			printf(" ");
		printf("a");
		system("clear");
		}
	for(i=19;i>=0;i--)
	{
		for(j=1;j<=i;j++)
			printf(" ");
		printf("a");
		system("clear");
		}	
}

