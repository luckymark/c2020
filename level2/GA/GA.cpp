#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include <time.h>
int LENGTH;
const int MAXN=200;//迷宫最大边长 
const int ITERATION=5;//进化迭代轮次 
const int INDIVIDUAL=1000;//个体总数 
const int WINNER=10;//可遗传个体 
const int MAX_STEP=100;//最多步数 
const int BONUS=10000;//终点奖励分数 
const int TRANS_PIECES=100;//遗传突变个数 
struct INDI
{
	int step[MAX_STEP+1];
	int point;
}indi[INDIVIDUAL+1],temp[INDIVIDUAL+1];
int maze[MAXN][MAXN];

struct node
{
	int x,y;
}q[MAXN*MAXN];
node start,end;
void Swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void Init()
{
	scanf("%d",&LENGTH);
	for(int i=1;i<=LENGTH;i++)
	for(int j=1;j<=LENGTH;j++)
	{
		scanf("%d",&maze[i][j]);
		if(maze[i][j]==0) start.x=i,start.y=j;
		if(maze[i][j]==3) end.x=i,end.y=j;
	}
}

void Born()
{
	srand(time(0));
	for(int i=1;i<=INDIVIDUAL;i++)
	for(int j=1;j<=MAX_STEP;j++)
	indi[i].step[j]=rand()%4;
}

void Sim()
{
	for(int i=1;i<=INDIVIDUAL;i++)
	{
		indi[i].point=0;
		int tem_x=start.x,tem_y=start.y;
		for(int j=1;j<=MAX_STEP;j++)
		{
			int jud=0;
			if(indi[i].step[j]==0&&maze[tem_x+1][tem_y]!=1) tem_x+=1;
			else if(indi[i].step[j]==1&&maze[tem_x-1][tem_y]!=1) tem_x-=1;
			else if(indi[i].step[j]==2&&maze[tem_x][tem_y+1]!=1) tem_y+=1;
			else if(indi[i].step[j]==3&&maze[tem_x][tem_y-1]!=1) tem_y-=1;
			if(maze[tem_x][tem_y]==3)
			{
				indi[i].point+=BONUS;
				break;
			}
			indi[i].point--;
		}
	}
}

void Copy(int x,int y,int jud)
{
	if(jud==1)
	{
		temp[y].point=indi[x].point;
		for(int i=1;i<=MAX_STEP+1;i++)
		temp[y].step[i]=indi[x].step[i];
	}
	else if(jud==0)
	{
		indi[x].point=temp[y].point;
		for(int i=1;i<=MAX_STEP+1;i++)
		indi[x].step[i]=temp[y].step[i];
	}
	else 
	{
		indi[y].point=indi[x].point;
		for(int i=1;i<=MAX_STEP+1;i++)
		indi[y].step[i]=indi[x].step[i];
	}
}

void Sort(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)/2;
	Sort(l,mid),Sort(mid+1,r);
	int lhead=l,rhead=mid+1;
	int cnt=0;
	while(cnt<r-l)
	{
		if(indi[lhead].point>indi[rhead].point&&lhead<=mid) 
		{
			Copy(lhead,l+cnt,1);
			lhead++;
		}
		else 
		{
			Copy(rhead,l+cnt,1);
			rhead++;
		}
		cnt++;
	}
	for(int i=l;i<=r;i++)
	Copy(i,i,0);
	return;
}
void Evolution()
{
	for(int i=1;i<=WINNER;i++)
	for(int j=1;j<=INDIVIDUAL/WINNER;j++)
	{
		int l=(INDIVIDUAL/WINNER-1)*i+2,r=(INDIVIDUAL/WINNER-1)*(i+1)+1;
		for(int k=l;k<=r;k++)
		{
			Copy(i,k,2);
			for(int ii=1;ii<=TRANS_PIECES;ii++)
			{
				int posi=rand()%MAX_STEP,direc=rand()%4;
				indi[k].step[posi]=direc;
			}
		}		
	}
}
void GA()
{
	Born();
	for(int i=1;i<=ITERATION;i++)
	{
		Sim();
		memset(temp,0,sizeof(temp));
		Sort(1,INDIVIDUAL);
		Evolution();
	}
}

int main()
{
	freopen("1.txt","r",stdin);
	Init();
	GA(); 
	printf("the least steps we found is %d",BONUS-indi[1].point);
	
} 
