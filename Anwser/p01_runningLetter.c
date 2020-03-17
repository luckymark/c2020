#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

# define WIDTH 120
# define LETTER "hello"
# define SIZE 5  

int main()
{		
	int now=1,i=1;
	int direction=1;
	while(1)
	{
		for(i=1;i<=WIDTH-SIZE;i++)
		{
			
			if(i==now)  
			{
				printf(LETTER);
			} 
			else
			{
			  printf(" ");
			} 
		}
		if(now==1 && direction<0)
		{
			direction=1;
			now++;
		}
		else
		if(now==WIDTH-SIZE && direction>0)
		{
			direction=-1;
			now--;
		}
		else 
		{
			now+=direction;
		} 
		Sleep(100);
		system("CLS");
	}
	
	return 0;
} 
