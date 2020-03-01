#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#define Width 40
#define landch 32//space 
#define wallch1 45//@ 
#define wallch2 124//| 
#define wallch3 64//_
#define charch 42//*
#define destch 36//$
#define refreshcnt 25
struct point
{
	int x,y;
}st,ed;
struct que
{
	struct point p;
	int dist;
};
int dx[5]={0,-1,1,0,0},dy[5]={0,0,0,-1,1};
int mp[Width+1][Width+1],mindis,curdis;
int width,minstep,bknum;
int checkdis()//check connecetion
{
	struct que q[width*width];
	int inq[Width][Width]={0},dist[width][width];
	memset(dist,0x3f,sizeof dist);
	int head=1,tail=0;
	dist[st.x][st.y]=0; 
	q[head].p=st,q[head].dist=0;
	inq[st.x][st.y]=1;
	while(head!=tail)
	{
		tail=(tail+1)%(width*width);
		struct que now=q[tail];
		inq[now.p.x][now.p.y]=0;
		int isdest=0;
		for(int i=1;i<=4;i++)
		{
			struct que nxt={now.p.x+dx[i],now.p.y+dy[i],now.dist+1};
			if((mp[nxt.p.x][nxt.p.y]==0||mp[nxt.p.x][nxt.p.y]==3)&&nxt.dist<dist[nxt.p.x][nxt.p.y])
			{
				dist[nxt.p.x][nxt.p.y]=nxt.dist;
				if(!inq[nxt.p.x][nxt.p.y])
				{
					inq[nxt.p.x][nxt.p.y]=1;
					head=(head+1)%(width*width); 
					q[head]=nxt;
				}
			}
		}
	}
	mindis=dist[ed.x][ed.y];
	return dist[ed.x][ed.y]!=0x3f3f3f3f&&dist[ed.x][ed.y]>minstep;
}
void makeblock()//put blocks
{
	for(int i=0;i<=width;i++)
		mp[i][0]=mp[i][width]=-1,mp[0][i]=mp[width][i]=-2;
	mp[0][0]=mp[width][0]=mp[0][width]=mp[width][width]=1;
	for(int i=1;i<=bknum;i++)
	{
		int tmpx=rand()%(width-1)+1,tmpy=rand()%(width-1)+1;
		while(mp[tmpx][tmpy]==1)
			tmpx=rand()%(width-1)+1,tmpy=rand()%(width-1)+1;
		mp[tmpx][tmpy]=1;
	}
	return;
}
void newmaze()//random maze making
{
	st.x=rand()%(width-1)+1,st.y=rand()%(width-1)+1,
	ed.x=rand()%(width-1)+1,ed.y=rand()%(width-1)+1;
	makeblock();int randcnt=0;
	while(ed.x==st.x&&ed.y==st.y||!checkdis())
	{
		++randcnt;
		if(randcnt==refreshcnt)memset(mp,0,sizeof mp),makeblock(),randcnt=0;
		st.x=rand()%(width-1)+1,st.y=rand()%(width-1)+1,
		ed.x=rand()%(width-1)+1,ed.y=rand()%(width-1)+1;
	}
	mp[st.x][st.y]=2;mp[ed.x][ed.y]=3;
	return;
}
void print()
{
	puts("MAZE:GIGAHARDMODE\n'*'->PLAYER '$'->DESTINATION '#'->WALL\nGO TO DESTINATION WITH MINIMUN STEPS!"); 
	printf("WIDTH:%d BKNUM:%d CURRENT_STEPS:%d MINDIS%d\n",width,bknum,curdis,mindis);
	for(int i=0;i<=width;i++)
	{
		for(int j=0;j<=width;j++)
		{
			switch(mp[i][j])
			{
				case -2:putchar(wallch1);break;
				case -1:putchar(wallch2);break;
				case 0:putchar(landch);break;
				case 1:putchar(wallch3);break;
				case 2:putchar(charch);break;
				case 3:putchar(destch);break;
			}
		}
		puts("");
	}
	return;
}
void move(int dir)
{
	int tmpx=st.x+dx[dir],tmpy=st.y+dy[dir];
	if(mp[tmpx][tmpy]==3)
	{
		mp[tmpx][tmpy]=2,mp[st.x][st.y]=0,st.x=tmpx,st.y=tmpy,curdis++;
		system("cls");
		printf("YOU WIN");
		if(curdis==mindis)puts(" WITH MINIMUN STEPS!");
		else printf(",HOWEVER YOU WASTED SOME STEPS...\nYOU USED %dSTEPS,MINIMUM STEPS ARE %dSTEPS\n",curdis,minstep);
		print();
		exit(0);
	}
	if(mp[tmpx][tmpy]==0)
		mp[tmpx][tmpy]=2,mp[st.x][st.y]=0,st.x=tmpx,st.y=tmpy,curdis++;
}
void init()//choose difficulty
{
	char ch;
	puts("PLEASE CHOOSE THE DIFFICULTY:\n");
	puts("1.KINDERGARDEN\n2.CAUSAL\n3.NORMAL\n4.HARD\n5.LUNATIC\n");
	while(scanf("%c",&ch))
	{
		if(ch=='1'){width=8;bknum=10;minstep=5;break;}
		if(ch=='2'){width=12;bknum=40;minstep=20;break;}
		if(ch=='3'){width=18;bknum=120;minstep=30;break;}
		if(ch=='4'){width=25;bknum=230;minstep=88;break;}
		if(ch=='5'){width=35;bknum=380;minstep=120;break;}
	}
	puts("LOADING...PLEASE WAIT A FEW SECENDS...");
	srand(time(NULL));
	newmaze();
	system("cls");
	print();
}
void start()
{
	char dir;
	while(dir=getch())
	{
		switch(dir)
		{
			case 72:move(1);break; 
			case 80:move(2);break; 
			case 75:move(3);break; 
			case 77:move(4);break;
		}
		system("cls");
		print();
	}
}
int main()
{
	init();
	start();
	return 0;
}
