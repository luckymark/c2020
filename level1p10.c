#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
#define MAPNUM 10
#define BLOCK '#'
#define PLAYER '@'
#define BOX '%'
#define DEST '*'
#define SIZE 12
#define RKNUM 5+2
#define STRLEN 20
int mp[MAPNUM][SIZE][SIZE];
int totmap,cur,curdis;
int dx[5]={0,-1,1,0,0},dy[5]={0,0,0,-1,1};
struct point
{
	int x,y;
}now[MAPNUM],nxt;
struct record
{
	char str[STRLEN];
	int step;
}rec[MAPNUM][RKNUM];
void print()
{
	for(int i=1;i<=mp[cur][1][0];i++)
	{
		for(int j=1;j<=mp[cur][0][1];j++)
		{
			switch(mp[cur][i][j])
			{
				case 0:putchar(' ');break;
				case 1:putchar(BLOCK);break;
				case 2:putchar(PLAYER);break;
				case 3:putchar(BOX);break;
				case 4:putchar(DEST);break;
				case 5:putchar(BOX);break;
				case 6:putchar(PLAYER);break;
			}
		}
		puts("");
	}
}
void init()
{
	puts("PLEASE INPUT YOUR NAME");
	scanf("%s",rec[0][0].str+1);
	FILE *file; 
	file=fopen("map.txt","r");
	while(fscanf(file,"%d",&totmap)!=EOF)
	{
		fscanf(file,"%d%d",&mp[totmap][1][0],&mp[totmap][0][1]);
		for(int i=1;i<=mp[totmap][1][0];i++)
		{
			for(int j=1;j<=mp[totmap][0][1];j++)
			{
				fscanf(file,"%d",&mp[totmap][i][j]);
				if(mp[totmap][i][j]==2)now[totmap]=(struct point){i,j};
			}
		}
	}
	fclose(file);
	printf("PLEASE CHOOSE A LEVEL FROM %d TO %d\n",1,totmap);
	scanf("%d",&cur);
	system("cls");
	print();
}
bool check()
{
	for(int i=1;i<=mp[cur][1][0];i++)
		for(int j=1;j<=mp[cur][0][1];j++)
			if(mp[cur][i][j]==3)return 0;
	return 1;
}
void upload()
{
	int mapid;
	printf("YOU WIN WITH %d STEPS\n",curdis);
	FILE *fp=fopen("rank.txt","r");
	while(fscanf(fp,"MAP:%d",&mapid)!=EOF)
	{
		for(int i=1;i<RKNUM-1;i++)
		{
			fscanf(fp,"%d%d%s",&i,&rec[mapid][i].step,rec[mapid][i].str+1);
		}
	}
	fclose(fp);
	fp=fopen("rank.txt","w");
	for(int i=1;i<=totmap;i++)
	{
		bool flag=0;
		fprintf(fp,"MAP:%d\n",i);
		for(int j=1;j<RKNUM-1;j++)
		{
			if(flag==0)
			{
				if(rec[i][j].step>curdis&&i==cur)
				{
					flag=1;
					fprintf(fp,"%d %d %s\n",j,curdis,rec[0][0].str+1);
				}
				else fprintf(fp,"%d %d %s\n",j,rec[i][j].step,rec[i][j].str+1);
			}
			else fprintf(fp,"%d %d %s\n",j,rec[i][j-1].step,rec[i][j-1].str+1);
		}
	}
	bool flag=0;
	printf("MAP:%d\n",cur);
	for(int j=1;j<RKNUM-1;j++)
	{
		if(flag==0)
		{
			if(rec[cur][j].step>curdis)
			{
				flag=1;
				printf("%d %d %s\n",j,curdis,rec[0][0].str+1);
			}
			else printf("%d %d %s\n",j,rec[cur][j].step,rec[cur][j].str+1);
		}
		else printf("%d %d %s\n",j,rec[cur][j-1].step,rec[cur][j-1].str+1);
	}
	exit(0);
}
void move(int dir)
{
	nxt=(struct point){now[cur].x+dx[dir],now[cur].y+dy[dir]};
	struct point nnxt=(struct point){nxt.x+dx[dir],nxt.y+dy[dir]};
	if(mp[cur][nxt.x][nxt.y]==1||
	(mp[cur][nxt.x][nxt.y]==3&&mp[cur][nnxt.x][nnxt.y]==1)||
	(mp[cur][nxt.x][nxt.y]==5&&mp[cur][nnxt.x][nnxt.y]==1)||
	(mp[cur][nxt.x][nxt.y]==3&&mp[cur][nnxt.x][nnxt.y]==3)||
	(mp[cur][nxt.x][nxt.y]==5&&mp[cur][nnxt.x][nnxt.y]==3)||
	(mp[cur][nxt.x][nxt.y]==3&&mp[cur][nnxt.x][nnxt.y]==5)||
	(mp[cur][nxt.x][nxt.y]==5&&mp[cur][nnxt.x][nnxt.y]==5))
		return;
	if(mp[cur][now[cur].x][now[cur].y]==5)
		mp[cur][now[cur].x][now[cur].y]=4;
	if(mp[cur][now[cur].x][now[cur].y]==6)
		mp[cur][now[cur].x][now[cur].y]=4;
	else mp[cur][now[cur].x][now[cur].y]=0;
	if(mp[cur][nxt.x][nxt.y]==3&&mp[cur][nnxt.x][nnxt.y]==0)
	{
		mp[cur][nxt.x][nxt.y]=2;
		mp[cur][nnxt.x][nnxt.y]=3;
	}
	if(mp[cur][nxt.x][nxt.y]==3&&mp[cur][nnxt.x][nnxt.y]==4)
	{
		mp[cur][nxt.x][nxt.y]=2;
		mp[cur][nnxt.x][nnxt.y]=5;
	}
	if(mp[cur][nxt.x][nxt.y]==5&&mp[cur][nnxt.x][nnxt.y]==4)
	{
		mp[cur][nxt.x][nxt.y]=6;
		mp[cur][nnxt.x][nnxt.y]=5;
	}
	if(mp[cur][nxt.x][nxt.y]==0)
		mp[cur][nxt.x][nxt.y]=2;
	if(mp[cur][nxt.x][nxt.y]==4)
		mp[cur][nxt.x][nxt.y]=6;
	now[cur]=nxt;
	curdis++;
	system("cls");
	print();
	if(check())upload();
}
int main()
{
	char ch;
	init();
	while(ch=getch())
	{
		switch(ch)
		{
		    case 72:move(1);break; 
		    case 80:move(2);break; 
			case 75:move(3);break; 
			case 77:move(4);break;
		}
	}
}
