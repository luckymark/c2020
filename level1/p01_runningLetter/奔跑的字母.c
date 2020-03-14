#include <stdio.h>
#include <windows.h>
int main()
{
	char a='A';
	for(int i=0;i<4;++i)
	{
		if(i%2==0)
		{
			for(int j=0;j<10;++j)
			{
				
				for(int z=0;z<j;++z)
				{
					printf(" ");
				}
				printf("%c",a);
				system("cls");
			}
		}
		else
		{
			for(int j=10;j>0;--j)
			{
			
				for(int z=0;z<j;++z)
				{
					printf(" ");
				}
					printf("%c",a);
				system("cls");
			}
		}
	}
	return 0;
} 
