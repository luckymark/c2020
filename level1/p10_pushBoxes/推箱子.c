#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define M 9
#define N 9
int x=1,y=1,score=100;
char a[M][N];
void start();
void map();
void choose(int num);
void move();
int main()
{
	start();
	int n;
	scanf("%d",&n);
	choose(n);
	if(n==1)
	{
		while(a[3][7]!=4)
		{
			system("cls");
			map();
			move();
			system("cls");
			
		}
	}
	else
	{
		while(a[4][1]!=4)
		{
			system("cls");
			map();
			move();
			system("cls");
			
		}
	}
	printf("you win! \n");
	printf("score:%d",score);
	FILE *w=fopen("score.txt","w");
	fprintf(w,"%d ",score);
	fclose(w);
	return 0;
}
void start()
{
	printf("\t\t\t\t\t欢 迎 来 到 推 箱 子 游 戏 游！\n");	
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("玩家:x   箱子:*   墙壁:#\n");
	printf("上:w/W 下:s/S 左:a/A 右:d/D \n");
	printf("请按1或2选择关卡:");

}
void map()
{
	int i,j;
	for(i=0;i<M;++i)
	{
		for(j=0;j<N;++j)
		{
			switch (a[i][j])
			{
				case 0 : printf("#");
				         break;
				case 1 : printf("x");
				         break;
				case 2 : printf(" ");
				         break;
				case 3 : printf("@");
				         break;
				case 4 : printf("*");
				         break;				         
				default: printf ("error");
			}
				
		}
		printf("\n");
	}
}

void choose(int num)
{
	FILE *fp=NULL;
	int i,j;
	if(num==1)
	{
		fp=fopen("map1.txt","r");
		for(i=0;i<M;++i)
		{
			for(j=0;j<N;++j)
			{
				fscanf(fp,"%d",&a[i][j]);
			}
		}
	fclose(fp);
	}
	else
	{
		fp=fopen("map2.txt","r");
		for(i=0;i<M;++i)
		{
			for(j=0;j<N;++j)
			{
				fscanf(fp,"%d",&a[i][j]);
			}
		} 
	fclose(fp);
	}
}
void move()
{
	char b;
	b=getch();
	score--;
	if(b=='s'||b=='S')
		{
			if(a[x+1][y]!=0)
			{
				if(a[x+1][y]==4 && a[x+2][y]!=0)
				{
					a[x][y]=2;
					x++;
					a[x][y]=1;
					a[x+1][y]=4;	
				}
				else if(a[x+1][y]!=4)
				{
					a[x][y]=2;
					x++;
					a[x][y]=1;
				}
			}
		}
	if(b=='w'||b=='W')
		{
			if(a[x-1][y]!=0)
			{
				if(a[x-1][y]==4 && a[x-2][y]!=0)
				{
					a[x][y]=2;
					x--;
					a[x][y]=1;
					a[x-1][y]=4;
				}
				else if(a[x-1][y]!=4)
				{
					a[x][y]=2;
					x--;
					a[x][y]=1;
				}
			}
		}
	if(b=='d'||b=='D')
		{
			if(a[x][y+1]!=0)
			{	
				if(a[x][y+1]==4 && a[x][y+2]!=0)
				{
					a[x][y]=2;
					y++;
					a[x][y]=1;
					a[x][y+1]=4;
				}
				else if(a[x][y+1]!=4)
				{
					a[x][y]=2;
					y++;
					a[x][y]=1;
				}
			}
			
		}
	if(b=='a'||b=='A')
		{
			if(a[x][y-1]!=0)
			{
				if(a[x][y-1]==4 && a[x][y-2]!=0)
				{
					a[x][y]=2;
					y--;
					a[x][y]=1;
					a[x][y-1]=4;
				}
				else if(a[x][y-1]!=4)
				{
					a[x][y]=2;
					y--;
					a[x][y]=1;
				}
			
			}
			
			
		}
	 
}
