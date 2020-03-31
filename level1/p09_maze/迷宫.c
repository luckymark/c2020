#include <stdio.h>
#include <windows.h>
void move();
void maze();
char a[100][100]={"##########",
				  "#x       #",
				  "# ## ##  #",
				  "#  #  #  #",
				  "#  #   # #",
				  "# #  # # #",
				  "#  #  ####",
				  "#   ##    ",
				  "#   @    #",
				  "##########",};
int x=1,y=1;
				  
int main()
{
	while(a[7][9]==' ')
	{
	maze();
	
	move();
	
	system("cls");
	}
	system("cls");
	
	printf("you win!");
} 

void move()
{
	char b;
	b=getch();
	
	if(b=='s')
		{
			if(a[x+1][y]!='#')
			{
				a[x][y]=' ';
				x++;
				a[x][y]='x';
			}
		}
	if(b=='w')
		{
			if(a[x-1][y]!='#')
			{
				a[x][y]=' ';
				x--;
				a[x][y]='x';
			}
		}
	if(b=='d')
		{
			if(a[x][y+1]!='#')
			{	
				if(a[x][y+1]=='@')
				{
					printf("你被传送回了起点！");
					Sleep(500);
					printf(". ");
					Sleep(1000);
					printf(". ");
					Sleep(1000);
					printf(". ");
					Sleep(100);
					a[x][y]=' ';
					x=1;
					y=1;
					a[x][y]='x'; 
					a[6][6]=' ';
				}
				else
				{
					a[x][y]=' ';
					y++;
					a[x][y]='x';
				}
			
			}
		
		}
	if(b=='a')
		{
			if(a[x][y-1]!='#')
			{
				if(a[x][y-1]=='@')
				{
					printf("【手动滑稽】");
					Sleep(1000);
					a[x][y]=' ';
					x=5;
					y=8;
					a[x][y]='x'; 
					a[4][8]='#';
				}
				else
				{
					a[x][y]=' ';
					y--;
					a[x][y]='x';
				}
			
			}
			
			
		}
	 
}

void maze()
{
	int i,j;
	
	for(i=0;i<10;++i)
		{
			
			for(j=0;j<10;++j)
			{
				printf("%c",a[i][j]);
			}
			
			printf("\n");
		 } 
		 
}
