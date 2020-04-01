#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
#include<string.h>
#define MAPH 50//3¡è 
#define MAPW 50// ?¨ª 
#define PNUM 10000//??¨¬?¨ºy 
#define FNUM 50//??¡ä¨²¨ºy 
#define GNUM 150//?¨´¨°¨°¨ºy
#define VNUM 5//¨ª?¡À?¨ºy 
#define ENUM 100//???¡¥¡ä¨²¨ºy
#define MINVAL -100000//?o?T?? 
#define MAXVAL 100000//?y?T?? 
struct
{
	int mp[MAPH+5][MAPW+5];
	int sx,sy,ex,ey;
	int n,m;
}map;
struct person
{
	int x,y,h,step,g[GNUM+5];
}p[PNUM+5],son[PNUM+5];
struct
{
	int id,h,step;//D¨°o? 
}mx;
void init()
{
	FILE *fp=fopen("map.in","r");
	int n,m;
	fscanf(fp,"size:%d*%d",&n,&m);
	map.n=n,map.m=m;
	char str[MAPW+5];
	for(int i=1;i<=n;i++)
	{
		fscanf(fp,"%s",str+1);
		for(int j=1;j<=m;j++)
		{
			if(str[j]=='0')map.mp[i][j]=0;
			else if(str[j]=='1')map.mp[i][j]=1;
			else if (str[j]=='2')
			{
				map.mp[i][j]=2;
				map.sx=i,map.sy=j;
			}
			else if(str[j]=='3')
			{
				map.mp[i][j]=3;///////////////////////////////
				map.ex=i,map.ey=j;
			}
		}
	}
	fclose(fp);
}
void born()
{
	srand(time(NULL));
	for(int i=1;i<=PNUM;i++)
		for(int j=1;j<=GNUM;j++)
			p[i].g[j]=rand()%4;
}
void cal()
{
	mx.h=MINVAL;
	for(int i=1;i<=PNUM;i++)
	{
		p[i].x=map.sx,p[i].y=map.sy;
		p[i].step=0,p[i].h=0;
		int tmpx,tmpy;
		for(int j=1;j<=GNUM;j++)
		{
			tmpx=p[i].x,tmpy=p[i].y;
			p[i].step++;
			if(p[i].g[j]==0)tmpx--;
			else if(p[i].g[j]==1)tmpy++;
			else if(p[i].g[j]==2)tmpy--;
			else if(p[i].g[j]==3)tmpx++;
			if((j>=2&&p[i].g[j]+p[i].g[j-1]==3)||map.mp[tmpx][tmpy]==2)p[i].h-=1000;//??¨ª¡¤?¡¤ 
			if(map.mp[tmpx][tmpy]==0)p[i].x=tmpx,p[i].y=tmpy;
			else if(map.mp[tmpx][tmpy]==1)p[i].h-=1000;//?? 
			else if(map.mp[tmpx][tmpy]==3)
			{
				p[i].h+=MAXVAL;
				p[i].x=tmpx,p[i].y=tmpy;
				break;
			}
		}
		if(map.mp[tmpx][tmpy]!=3)
			p[i].h-=(p[i].x-map.ex)*(p[i].x-map.ex)+(p[i].y-map.ey)*(p[i].y-map.ey);
		if(p[i].h>mx.h)
		{
			mx.h=p[i].h;
			mx.id=i;
			mx.step=p[i].step;
		}
	}
}
bool cmp(struct person a,struct person b){return a.h>b.h;}
void evolution()
{
	srand(time(NULL));
	sort(p+1,p+PNUM+1,cmp);
	int dad,mom;
	int num=0;
	for(int i=1;i<=FNUM;i++)
	{
		num++;
		for(int j=1;j<=GNUM;j++)
			son[i].g[j]=p[i].g[j];
	}
	for(int i=num;i<=PNUM;i++)
	{
		do
		{
			dad=rand()%FNUM,mom=rand()%FNUM;
		}while(dad==mom);
		int tmp=rand()%GNUM;/////////////////////////
		for(int j=1;j<=tmp;j++)son[i].g[j]=p[dad].g[j];
		for(int j=tmp+1;j<=GNUM;j++)son[i].g[j]=p[mom].g[j];
	}
	for(int i=1;i<=PNUM;i++)
	{
		int v=rand()%VNUM;
		for(int j=1;j<=GNUM;j++)p[i].g[j]=son[i].g[j];
		for(int j=1;j<=v;j++)
		{
			int tmp=rand()%GNUM;
			int newg;
			do
			{
				newg=rand()%4;
			}while(newg==p[i].g[j]);
			p[i].g[tmp]=newg;
		}
	}
}
void print()
{
	system("cls");
	for(int i=1;i<=map.n;i++)
	{
		for(int j=1;j<=map.m;j++)
		{
			printf("%d ",map.mp[i][j]);
		}
		puts("");
	 } 
}
void printans()
{
	if(mx.h<0)
	{
		puts("Way is not found.");
		exit(0);
	}
	int tmpx=map.sx,tmpy=map.sy,nowx=map.sx,nowy=map.sy;
	for(int i=1;i<=GNUM;i++)
	{
		if(p[mx.id].g[i]==0)tmpx--;
		if(p[mx.id].g[i]==1)tmpy++;
		if(p[mx.id].g[i]==2)tmpy--;
		if(p[mx.id].g[i]==3)tmpx++;
		if(map.mp[tmpx][tmpy]==1)tmpx=nowx,tmpy=nowy;
		else 
		{
			map.mp[nowx][nowy]=0;
			nowx=tmpx,nowy=tmpy;
			if(map.mp[tmpx][tmpy]==3)
			{
				map.mp[nowx][nowy]=2;
				print();
				return;
			}
			map.mp[nowx][nowy]=2;
			Sleep(100);
			print();
		}
	}
}
int main()
{
	init();
	print();
	clock_t st,ed;
	st=clock();
	born();
	cal();
	for(int i=1;i<=ENUM;i++)
	{
		evolution();
		cal();
	}
	ed=clock();
	printans(); 
	printf("total steps:%d\ncal sec:%d",mx.step,(ed-st)/CLOCKS_PER_SEC);
	return 0;
}

