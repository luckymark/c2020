#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
const int LENGTH=10;
const int MAXN=200;
int maze[MAXN][MAXN];

struct node
{
	int x,y;
}q[MAXN*MAXN];

void Swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void Create_map()
{
	for(int i=0;i<=LENGTH;i++)
	maze[i][0]=maze[0][i]=maze[LENGTH+1][i]=maze[i][LENGTH+1]=1;	
	int head=0,tail=1;
	q[1].x=q[1].y=2;
	while(head<tail)
	{
		head++;
		int r=head+(rand()%(tail-head+1));
		int xx=q[r].x,yy=q[r].y;
		int count=0;
		for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)
		if(abs(i)+abs(j)==1&&maze[xx+i][yy+j]) count++;
		if(count<=1)
		{
			maze[xx][yy]=1;
			for(int i=-1;i<=1;i++)
			for(int j=-1;j<=1;j++)
			if(abs(i)+abs(j)==1&&(!maze[xx+i][yy+j])) 
			{
				tail++;
				q[tail].x=xx+i;
				q[tail].y=yy+j;
			}
		}
		int tem=q[r].x;
		q[r].x=q[head].x;
		q[head].x=tem;
		tem=q[r].y;
		q[r].y=q[head].y;
		q[head].y=tem;
	}
	for(int i=LENGTH;i>=0;i--)
	if(maze[LENGTH][i]==0&&maze[LENGTH-1][i]==1)
	{
		maze[LENGTH][i]=2;
		break;
	}
}
void Draw(int xx,int yy)
{
	for(int i=1;i<=LENGTH;i++)
	{
		for(int j=1;j<=LENGTH;j++)
		if(i==xx&&j==yy) printf("i");
		else if(maze[i][j]==0) printf("0");
		else if(maze[i][j]==1)printf(" ");
		else printf("t");
		printf("\n");
	}
	
}
void P_note()
{
	printf("hello! you are the 'i' in the maze,try to press up, down, left&right to reach 't'!\n");
}
void E_note()
{
	printf("you have win the game! congratulations!\n");
}
int main()
{
	freopen("1.txt","w",stdout); 
	Create_map();
	node play;
	play.x=2,play.y=2;
	while(1)
	{
		if(maze[play.x][play.y]==2)
		{
			E_note();
			return 0;
		}
		P_note();
		Draw(play.x,play.y);
		char move;
		move=getch();
		if(move==72&&maze[play.x-1][play.y]!=0)  play.x-=1; 
        else if(move==80&&maze[play.x+1][play.y]!=0)  play.x+=1;
        else if(move==75&&maze[play.x][play.y-1]!=0)  play.y-=1;
		else if(move==77&&maze[play.x][play.y+1]!=0)  play.y+=1;
		system("cls");
	}
	
} 
