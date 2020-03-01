#include<stdio.h>
#include<windows.h>
#define fps 60
#define width 30
int main()
{
	int dir=1;
	while(1)
	{
		for(int i=dir==1?1:width;i<=width&&i>=0;i+=dir)
		{
			for(int j=0;j<i;j++)
				putchar(' ');
			putchar('A');
			Sleep(1000/fps);
			system("cls");
		}
		dir*=-1;
	}
	return 0;
}
