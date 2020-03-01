#include<stdio.h>

int main()
{
	for(int i=1;i<=1000;i++)
	{
		if(!(i%7)&&!(i%12))
		{
			int x=i/6+i/12+i/7+i/2;
			if(x+9==i)
			{
				printf("Diophantus is %d years old",i);
				return 0;
			}
		}
	}
} 
