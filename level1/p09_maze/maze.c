#include<stdio.h>
#include<windows.h>
#define X 10
#define Y 10

int map[X][Y]=
{
{0,0,0,0,0,0,0,0,0,0},
{0,1,2,2,2,2,2,2,0,0},
{0,2,0,0,0,2,0,2,0,0},
{0,2,0,0,0,2,0,2,0,0},
{0,2,2,2,0,0,0,2,0,0},
{0,0,0,2,2,0,0,2,0,0},
{0,0,0,0,2,2,2,2,2,0},
{0,0,0,0,0,0,2,0,0,0},
{0,0,0,0,0,0,2,2,2,0},
{0,0,0,0,0,0,0,0,3,0},
};


void remakemap();
int find();
int move();
int up();
int down();
int left();
int right();

int main()
{
	printf("请按任意键开始迷宫游戏\n"); 
	printf("请按w、s、a、d进行上下左右移动");
	while(getch())
	{
	system("cls");
	remakemap();
	break;
	}
	while(move()){
		system("cls");
	    remakemap();
		}
	printf("恭喜通关！");
	return 0;
}

void remakemap()
{
	int i,j;
	for(i=0;i<=X-1;i++){
		for(j=0;j<=Y-1;j++){
			switch (map[i][j])
			{
				case 0 : printf("■");
				         break;
				case 1 : printf("♂");
				         break;
				case 2 : printf("  ");
				         break;
				case 3 : printf("☆");
				         break;
				default: printf ("error");
			}
		}
		printf("\n");
	}
}


int find(int *m,int *n)
{
	int i,j;	
	for(i=0;i<=X-1;i++)
	{
		for(j=0;j<=Y-1;j++)
		{
			if (map[i][j]==1)
			{
				*m=i;
				*n=j;
			}
		}
    }
}


int move()
{
	int i=0;
    int j=0;
    find(&i,&j);	
    switch (getch())
	{
		case 'w': up(i,j);
		break;
		case 'W': up(i,j);
		break;
		case 's': down(i,j);
		break;
		case 'S': down(i,j);
		break;
		case 'a': left(i,j);
		break;
		case 'A': left(i,j);
		break;
		case 'd': right(i,j);
		break;	
		case 'D': right(i,j);
		break;	
	}
	if(map[i][j]==3)
	{
		return 0;
	}else {
		return 1;
	}
}

int right(int q,int p)
{
	int i,j;
	i=q;
	j=p;
	if(map[i][j+1]==2){
		map[i][j+1]=1;
		map[i][j]=2;
	}else if(map[i][j+1]==3){
		map[i][j]=3;
	}
}

int left(int q,int p)
{
	int i,j;
	i=q;
	j=p;
	if(map[i][j-1]==2){
		map[i][j-1]=1;
		map[i][j]=2;
	}else if(map[i][j-1]==3){
		map[i][j]=3;
	}
}

int up(int q,int p)
{
	int i,j;
	i=q;
	j=p;
	if(map[i-1][j]==2){
		map[i-1][j]=1;
		map[i][j]=2;
	}else if(map[i-1][j]==3){
		map[i][j]=3;
	}
}

int down(int q,int p)
{
	int i,j;
	i=q;
	j=p;
	if(map[i+1][j]==2){
		map[i+1][j]=1;
		map[i][j]=2;
	}else if(map[i+1][j]==3){
		map[i][j]=3;
	}
}

