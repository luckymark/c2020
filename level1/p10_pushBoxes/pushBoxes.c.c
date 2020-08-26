#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#define X 9
#define Y 9
#define Num 3
#define alllevel 2


int map[alllevel][X][Y];
int destionX[alllevel][Num];
int destionY[alllevel][Num];
int level;
int * numscore;


void remakemap();
void find(int *m,int *n);
//int find3();
int move();
int up(int q,int p);
int down(int q,int p);
int left(int q,int p);
int right(int q,int p);
int upmove(int q,int p);
int downmove(int q,int p);
int leftmove(int q,int p);
int rightmove(int q,int p);
void game();


int main()
{
	int n,m;
	numscore=(int *)malloc(sizeof(int));
	int a=0;
	numscore = &a;
	FILE * fp = NULL;
	FILE * sc = NULL;
	fp = fopen("map.txt","r");
	sc = fopen("score.txt","w+");
	
	for(n=0;n<X;n++)
	{
		for(m=0;m<Y;m++)
		{
			fscanf(fp,"%d",&map[0][n][m]);
		}
	}
	for(n=0;n<Num;n++)
	{
		fscanf(fp,"%d",&destionX[0][n]);
	}
	for(n=0;n<Num;n++)
	{
		fscanf(fp,"%d",&destionY[0][n]);
	}
		
	for(n=0;n<X;n++)
	{
		for(m=0;m<Y;m++)
		{
			fscanf(fp,"%d",&map[1][n][m]);
		}
	}

	for(n=0;n<Num;n++)
	{
		fscanf(fp,"%d",&destionX[1][n]);
	}

	for(n=0;n<Num;n++)
	{
		fscanf(fp,"%d",&destionY[1][n]);
	}

	
	fclose(fp);
    game();
    fprintf(sc,"%d",*numscore);
    fclose(sc);
	return 0;
}


void game()
{
		
	printf("请按任意键开始迷宫游戏\n"); 
	printf("请按w、s、a、d进行上下左右移动");
	while(getch())
	{
	system("cls");
	printf("输入关卡书后请按回车  ");
	printf("你想进去的关卡（1/2）： ");
	scanf("%d",&level);
	break;
	}
	level =level-1;
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
	system("cls");
	remakemap();
	printf("恭喜通关！");
}


void remakemap()
{
	int i,j;
	for(i=0;i<=X-1;i++){
		for(j=0;j<=Y-1;j++){
			switch (map[level][i][j])
			{
				case 0 : printf("■");
				         break;
				case 1 : printf("♂");
				         break;
				case 2 : printf("  ");
				         break;
				case 3 : printf("★");
				         break;
				case 4 : printf("□");
				         break;				         
				default: printf ("error");
			}
		}

		printf("\n");
	}

}


void find(int *m,int *n)
{
	int i,j;	
	for(i=0;i<=X-1;i++)
	{
		for(j=0;j<=Y-1;j++)
		{
			if (map[level][i][j]==1)
			{
				*m=i;
				*n=j;
			}
		}
    }
}


int move()
{
	int m;
	int n=0;
	int i=0;
    int j=0;
    int p,q;
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

	for(m=0;m<Num;m++)
	{
		if(map[level][destionY[level][m]][destionX[level][m]]==4)
		{
			n++;
		}
	}
	
	find(&p,&q);
	if(p!=i||q!=j)
	{
		*numscore=*numscore+1;
	}

	if(n==Num)
	{
		return 0;
	}else {
		return 1;
	}  

}

int right(int q,int p)
{
	int i,j,m;
	i=q;
	j=p;
	if(map[level][i][j+1]!=0)
	{
	if(map[level][i][j+1]==4)
	{
	rightmove(i,j);
		
	}else if(map[level][i][j+1]==2||3)
		{
		    map[level][i][j+1]=1;
		    map[level][i][j]=2;
	    }
	}

	for(m=0;m<Num;m++)
	{
		if(destionX[level][m]==j&&destionY[level][m]==i)
			{
				int p,q;
				find(&p,&q);
				if(p==i&&q==j)
				{
				}else 
				{
				map[level][i][j]=3;
				}

	    	}
	}
}

int left(int q,int p)
{
	int i,j,m;
	i=q;
	j=p;
	if(map[level][i][j-1]!=0)
	{
	if(map[level][i][j-1]==4)
	{
		leftmove(i,j);
	}else if(map[level][i][j-1]==2||3)
		{
		    map[level][i][j-1]=1;
		    map[level][i][j]=2;
	    }
	}
	for(m=0;m<Num;m++)
	{
		if(destionX[level][m]==j&&destionY[level][m]==i)
			{
				int p,q;
				find(&p,&q);
				if(p==i&&q==j)
				{
				}else 
				{
				map[level][i][j]=3;
				}

	    	}
	}

}

int up(int q,int p)
{
	int i,j,m;
	i=q;
	j=p;
	if(map[level][i-1][j]!=0)
	{
	if(map[level][i-1][j]==4)
	{
		upmove(i,j);
	}else if(map[level][i-1][j]==2||3)
	   {
		    map[level][i-1][j]=1;
		    map[level][i][j]=2;
	   }
	}
	for(m=0;m<Num;m++)
	{
		if(destionX[level][m]==j&&destionY[level][m]==i)
			{
				int p,q;
				find(&p,&q);
				if(p==i&&q==j)
				{
				}else 
				{
				map[level][i][j]=3;
				}

	    	}
	}


}

int down(int q,int p)
{
	int i,j,m;
	i=q;
	j=p;
	if(map[level][i+1][j]!=0)
	{
	if(map[level][i+1][j]==4)
	{
		downmove(i,j);
	}else if(map[level][i+1][j]==2||3)
		{
	     	map[level][i+1][j]=1;
	    	map[level][i][j]=2;
	    }
	}
	for(m=0;m<Num;m++)
	{
		if(destionX[level][m]==j&&destionY[level][m]==i)
			{
				int p,q;
				find(&p,&q);
				if(p==i&&q==j)
				{
				}else 
				{
				map[level][i][j]=3;
				}

	    	}
	}

}


int upmove(int q,int p)
{
	int i,j;
	i=q;
	j=p;
	if(map[level][i-2][j]==2){
		map[level][i-2][j]=4;
		map[level][i-1][j]=1;
		map[level][i][j]=2;
	}else if(map[level][i-2][j]==3)
	{
		map[level][i-2][j]=4;
		map[level][i-1][j]=1;
		map[level][i][j]=2;		
	}

}

int downmove(int q,int p)
{
	int i,j;
	i=q;
	j=p;
	if(map[level][i+2][j]==2){
		map[level][i+2][j]=4;
		map[level][i+1][j]=1;
		map[level][i][j]=2;
	}else if(map[level][i+2][j]==3)
	{
		map[level][i+2][j]=4;
		map[level][i+1][j]=1;
		map[level][i][j]=2;
	}
}

int leftmove(int q,int p)
{
	int i,j;
	i=q;
	j=p;
	if(map[level][i][j-2]==2){
		map[level][i][j-2]=4;
		map[level][i][j-1]=1;
		map[level][i][j]=2;
	}else if(map[level][i][j-2]==3)
	{
		map[level][i][j-2]=4;
		map[level][i][j-1]=1;
		map[level][i][j]=2;
	}
}

int rightmove(int q,int p)
{
	int i,j;
	i=q;
	j=p;
	if(map[level][i][j+2]==2){
		map[level][i][j+2]=4;
		map[level][i][j+1]=1;
		map[level][i][j]=2;
	}else if(map[level][i][j+2]==3)
	{
		map[level][i][j+2]=4;
		map[level][i][j+1]=1;
		map[level][i][j]=2;
	}

}
