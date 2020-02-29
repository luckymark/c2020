#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
int LENGTH;
const int MAXN=200;
char name[6];
int maze[MAXN][MAXN];

struct node
{
	int x,y;
}q[MAXN*MAXN];

void Draw(int xx,int yy)
{
	for(int i=1;i<=LENGTH;i++)
	{
		for(int j=1;j<=LENGTH;j++)
		if(i==xx&&j==yy) printf("i");
		else if(maze[i][j]==0)printf("x");
		else if(maze[i][j]==1)printf(" ");
		else if(maze[i][j]==2)printf("l");
		else if(maze[i][j]==3)printf("p");
		printf("\n");
	}
	
}
void P_note(int point)
{
	printf("Hello! You are the 'i' in the maze,try to push all the 'l' into the 'p'!\n");
	printf("Your current point is: %d\n",point);
}
void E_note(int x)
{
	printf("You have win the game! Congratulations!\n");
	printf("Your final point is %d",x);
}
void Read_maze(int x)
{
	name[0]='0'+x;
	name[1]='.';
	name[2]='i';
	name[3]='n';
	freopen(name,"r",stdin);
	scanf("%d",&LENGTH);
	for(int i=1;i<=LENGTH;i++)
	for(int j=1;j<=LENGTH;j++)
	scanf("%d",&maze[i][j]);

}

bool Check()
{
	int jud=1;
	for(int i=1;i<=LENGTH;i++)
	for(int j=1;j<=LENGTH;j++)
	if(maze[i][j]==3) jud=0;
	return jud;
}

int main()
{
	printf("please choose your level!(1-3)");
	int level;
	scanf("%d",&level);
	Read_maze(level);
	node play;
	play.x=play.y=2;
	int count=10000;
	while(1)
	{ 
		if(Check()) 
		{
			E_note(count);
			name[2]='o';
			name[3]='u';
			name[4]='t';
			freopen(name,"w",stdout);
			printf("Your final point in level %d is %d",level,count);
			break;
		}
		P_note(count);
		Draw(play.x,play.y);
		char move;
		move=getch();
		int m_x=0,m_y=0;
		if(move==72)  m_x=-1; 
   		else if(move==80)  m_x=1;
    	else if(move==75)  m_y=-1;
		else if(move==77)  m_y=1;
		if(maze[play.x+m_x][play.y+m_y]==1)
		{
			play.x+=m_x;
			play.y+=m_y;
		}
		else if(maze[play.x+m_x][play.y+m_y]==2&&maze[play.x+m_x*2][play.y+m_y*2]!=0)
		{
			if(maze[play.x+m_x*2][play.y+m_y*2]==3) maze[play.x+m_x*2][play.y+m_y*2]=1,count+=10000;
			else maze[play.x+m_x*2][play.y+m_y*2]=2;
			maze[play.x+m_x][play.y+m_y]=1;
			play.x+=m_x;
			play.y+=m_y;
		}
			if(count>=100) count-=100;
		system("cls");
	
	}
	
} 
