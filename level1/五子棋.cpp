#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#include<windows.h>
#include<conio.h>
#define MAXN 225
#define MAXM 15

typedef struct			//坐标
{
	int pointx;
	int pointy;
}Point;

typedef struct
{
	int dir[4];
	int win5;
	int alive4,die4;
	int alive3,die3;
	int alive2,die2;
	int alive1,die1;
	int score;
	Point left[4];
	Point right[4];
}Score;


void game_init();		//初始化
void game_start();		//游戏主程序
void get_num(Score sco[][MAXM], int color, int x, int y);
void get_state(Score sco[][MAXM], int color);
void get_score(Score sco[][MAXM],int add[]);

Score sco_player[MAXM][MAXM],sco_ai[MAXM][MAXM];
Point cursor[MAXN];					//标记棋盘255个点
Point player[MAXN],ai[MAXN];		//标记下棋顺序
int playturn = 0;		//0:黑棋; 1:白棋; 224:平局
int maps[MAXM][MAXM];	//记录棋盘
int add_ai[]={10000,200,50,30,8,2,2,1,1};	//根据状态得分值
int add_player[]={1000,100,20,10,5,1,1,0,0};

void game_init()
{
	int i,j;
	playturn=0;
	memset(maps,-1,sizeof(maps));
	memset(sco_player,0,sizeof(sco_player));
	memset(sco_ai,0,sizeof(sco_ai));
	setlinecolor(DARKGRAY);
	setlinestyle(PS_SOLID);
	setfillcolor(RGB(248, 232, 183));				//棋盘颜色
	fillrectangle(-1, -1, 601, 601);				
	for (i=0; i<14;i++)
	{
		for (j=0;j<14;j++)
		{
			rectangle(50+j*30,25+i*30,80+j*30,55+i*30);  //棋盘第一点是50 25
			cursor[i*15+j].pointx=50+j*30;
			cursor[i*15+j].pointy=25+i*30;
			ai[i*15+j].pointx=50+j*30;
			ai[i*15+j].pointy=25+i*30;
		}
		cursor[i*15+j].pointx=50+j*30;
		cursor[i*15+j].pointy=25+i*30;
		ai[i*15+j].pointx=50+j*30;
		ai[i*15+j].pointy=25+i*30;
	}
	for(j=0;j<14;j++)
	{
		cursor[i*15+j].pointx=50+j*30;
		cursor[i*15+j].pointy=25+i*30;
		ai[i*15+j].pointx=50+j*30;
		ai[i*15+j].pointy=25+i*30;
	}
	cursor[i*15+j].pointx=50+j*30;
	cursor[i*15+j].pointy=25+i*30;
	ai[i*15+j].pointx=50+j*30;
	ai[i*15+j].pointy=25+i*30;
	//标记棋盘5个点
	Point p[6];
	p[1].pointx=140,p[1].pointy=115;
	p[2].pointx=380,p[2].pointy=115;
	p[3].pointx=260,p[3].pointy=235;
	p[4].pointx=140,p[4].pointy=355;
	p[5].pointx=380,p[5].pointy=355;
	setfillcolor(DARKGRAY);
	setlinestyle(PS_SOLID);
	for(i=1;i<=5;i++)
	{
		fillcircle(p[i].pointx,p[i].pointy,2);

	}
	game_start();
}

void clue_print(int num)
{
	settextstyle(20,0,"宋体");
	if(num%2==0)
	{
		settextcolor(RGB(0,0,0));
		setbkmode(TRANSPARENT);
		outtextxy(330, 470, "白子执棋(电脑)");
		settextcolor(RGB(0,150,0));
		outtextxy(50, 470,"黑子执棋(玩家)");
	}
	else
	{
		settextcolor(RGB(0,0,0));
		setbkmode(TRANSPARENT);
		outtextxy(50, 470, "黑子执棋(玩家)");
		settextcolor(RGB(0,150,0));
		outtextxy(330, 470, "白子执棋(电脑)");
	}
}

void judge(int play)
{
	int i,j,k,num,flag;
	if(playturn+1==224)	//平局
	{
		setlinecolor(RGB(248, 232, 183));
		setfillcolor(RGB(248, 232, 183));
		fillrectangle(50,470,480,500);
		settextcolor(BLACK);
		settextstyle(40,0,"宋体");
		outtextxy(50,460,"平局,按任意键进入新游戏");
		system("pause");
		game_init();
	}
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			if(maps[i][j]==play)
			{
				//向右
				num=0,flag=0;
				for(k=0;k<5;k++)
				{
					if(j+k==15) break;
					if(maps[i][j+k]!=play) break;
					num+=1;
					if(num==5)
					{
						flag=1;
						break;
					}
				}
				if(flag==1) break;
				//向下
				num=0,flag=0;
				for(k=0;k<5;k++)
				{
					if(i+k==15) break;
					if(maps[i+k][j]!=play) break;
					num+=1;
					if(num==5)
					{
						flag=1;
						break;
					}
				}
				if(flag==1) break;
				//向右下
				num=0,flag=0;
				for(k=0;k<5;k++)
				{
					if(i+k==15||j+k==15) break;
					if(maps[i+k][j+k]!=play) break;
					num+=1;
					if(num==5)
					{
						flag=1;
						break;
					}
				}
				if(flag==1) break;
				//向左下
				num=0,flag=0;
				for(k=0;k<5;k++)
				{
					if(i+k==15||j-k==-1) break;
					if(maps[i+k][j-k]!=play) break;
					num+=1;
					if(num==5)
					{
						flag=1;
						break;
					}
				}
			}
			if(flag==1) break;
		}
		if(flag==1) break;
	}
	if(flag==1)
	{
		if(play==0)
		{
			setlinecolor(RGB(248, 232, 183));
			setfillcolor(RGB(248, 232, 183));
			fillrectangle(50,470,480,500);
			settextcolor(BLACK);
			settextstyle(30,0,"宋体");
			outtextxy(50,460,"黑子胜出,按任意键进入新游戏");
			system("pause");
			game_init();
		}
		else
		{
			setlinecolor(RGB(248, 232, 183));
			setfillcolor(RGB(248, 232, 183));
			fillrectangle(50,470,480,500);
			settextcolor(BLACK);
			settextstyle(30,0,"宋体");
			outtextxy(50,460,"白子胜出,按任意键进入新游戏");
			system("pause");
			game_init();
		}
	}
}

Point AIPlay()
{
	int i,j;
	memset(sco_player,0,sizeof(sco_player));
	memset(sco_ai,0,sizeof(sco_ai));
	for(i=0;i<MAXM;i++)
	{
		for(j=0;j<MAXM;j++)
		{
			if(maps[i][j]==-1)
			{
				maps[i][j] = 0;	//先标记为0
				get_num(sco_player,0,i,j);
				maps[i][j] = 1;
				get_num(sco_ai,1,i,j);
				maps[i][j] = -1;
			}
		}
	}
	get_state(sco_player,0);
	get_state(sco_ai,1);
	get_score(sco_player,add_player);
	get_score(sco_ai,add_ai);

	int score=0;
	Point pselect;
	for(i=0;i<MAXM;i++)
	{
		for(j=0;j<MAXM;j++)
		{
			if(sco_player[i][j].score+sco_ai[i][j].score>=score)
			{
				score=sco_player[i][j].score+sco_ai[i][j].score;
				pselect.pointx=50+j*30;
				pselect.pointy=25+i*30;
			}
		}
	}
	
	return pselect;
}

int coordinate(int x,int y)
{
	if(x>=0&&x<MAXM&&y>=0&&y<MAXM) return 1;
	return 0;
}

void get_num(Score sco[][MAXM], int color, int x, int y)
{
	int a, b;
	//左右方向
	a = x,b = y;
	//左面
	while (coordinate(a,b-1)==1&&maps[a][b-1]==color)
	{
		sco[x][y].dir[0]+=1;
		b -= 1;
	}
	b-=1;
	sco[x][y].left[0].pointx=a;
	sco[x][y].left[0].pointy=b;
	//还原落子位置
	a = x,b = y;
	//右面
	while (coordinate(a,b+1)==1&&maps[a][b+1]==color)
	{
		sco[x][y].dir[0]+=1;
		b += 1;
	}
	b+=1;
	sco[x][y].right[0].pointx=a;
	sco[x][y].right[0].pointy=b;
	sco[x][y].dir[0]+=1;
	//竖直方向
	a = x,b = y;
	while (coordinate(a-1,b)==1&&maps[a-1][b]==color)
	{
		sco[x][y].dir[1]+=1;
		a-=1;
	}
	a-=1;
	sco[x][y].left[1].pointx=a;
	sco[x][y].left[1].pointy=b;
	a = x,b = y;
	while (coordinate(a+1,b)==1&&maps[a+1][b]==color)
	{
		sco[x][y].dir[1]+=1;
		a+=1;
	}
	a+=1;
	sco[x][y].right[1].pointx=a;
	sco[x][y].right[1].pointy=b;
	sco[x][y].dir[1]+=1;
	//45度方向
	a = x,b = y;
	while (coordinate(a-1,b-1)==1&&maps[a-1][b-1]==color)
	{
		sco[x][y].dir[2]+=1;
		a -= 1;
		b -= 1;
	}
	a-=1,b-=1;
	sco[x][y].left[2].pointx=a;
	sco[x][y].left[2].pointy=b;
	a = x, b = y;
	while (coordinate(a+1,b+1)==1&&maps[a+1][b+1]==color)
	{
		sco[x][y].dir[2]+=1;
		a += 1;
		b += 1;
	}
	a+=1,b+=1;
	sco[x][y].right[2].pointx=a;
	sco[x][y].right[2].pointy=b;
	sco[x][y].dir[2]+=1;

	//135度方向
	a = x,b = y;
	while (coordinate(a+1,b-1)==1&&maps[a+1][b-1]==color)
	{
		sco[x][y].dir[3]+=1;
		a += 1;
		b -= 1;
	}
	a+=1,b-=1;
	sco[x][y].left[3].pointx=a;
	sco[x][y].left[3].pointy=b;
	a = x,b = y;
	while (coordinate(a-1,b+1)==1&&maps[a-1][b+1]==color)
	{
		sco[x][y].dir[3]+=1;
		a -= 1;
		b += 1;
	}
	a-=1,b+=1;
	sco[x][y].right[3].pointx=a;
	sco[x][y].right[3].pointy=b;
	sco[x][y].dir[3]+=1;
}

void get_state(Score sco[][MAXM], int color)
{
	int i,j,k;
	int hiscolor=color^1;
	int flag1,flag2;
	int left,right;
	for(i=0;i<MAXM;i++)
	{
		for(j=0;j<MAXM;j++)
		{
			if(maps[i][j]==0||maps[i][j]==1) continue;
			for(k=0;k<4;k++)	//四个方向上分别计算score值
			{
				left=maps[sco[i][j].left[k].pointx][sco[i][j].left[k].pointy];
				right=maps[sco[i][j].right[k].pointx][sco[i][j].right[k].pointy];
				flag1=coordinate(sco[i][j].left[k].pointx,sco[i][j].left[k].pointy);
				flag2=coordinate(sco[i][j].right[k].pointx,sco[i][j].right[k].pointy);
				int num=sco[i][j].dir[k];
				if(num>=5)//5
					sco[i][j].win5+=1;
				else if(num==4)//4
				{
					if (flag1==1&&flag2==1&&left==-1&&right==-1)	//_****_
						sco[i][j].alive4+=1;
					else if((flag1==1&&left==-1)||(flag2==1&&right==-1))	//_**** or ****_
						sco[i][j].die4+=1;
				}
				else if (num == 3) //3
				{
					if (flag1==1&&left==-1&&flag2==1&&right==-1)	//_***_
					{
						sco[i][j].alive3+=1;
					}
					else if ((flag1&&left==-1)||(flag2&&right==-1))	//_*** or ***_
					{
						sco[i][j].die3+=1;
					}
				}
				else if(num==2)	//2
				{
					if(flag1&&left==-1&&flag2&&right==-1)//_**_
					{
						sco[i][j].alive2+=1;
					}
					else if ((flag1&&left == -1) ||(flag2&& right == -1))//_** or **_
					{
						sco[i][j].die2+=1;
					}
				}
				else if (num == 1) //1
				{
					if (flag1&&left == -1 &&flag2&&right == -1)	//_*_
						sco[i][j].alive1+=1;
					
					else if ((flag1&&left == -1) || (flag2&&right == -1))	//_* or *_
						sco[i][j].die1+=1;

				}
			}
		}
	}
}

void get_score(Score sco[][MAXM],int add[])
{
	int i,j;
	for(i=0;i<MAXM;i++)
	{
		for(j=0;j<MAXM;j++)
		{
			if(maps[i][j]!=-1)	continue;
			if(sco[i][j].win5>=1)
				sco[i][j].score=add[0];
			else if(sco[i][j].alive4>=1)
				sco[i][j].score=add[1];
			else if(sco[i][j].die4>=2)
				sco[i][j].score=add[2];
			else if(sco[i][j].alive3>=1)
				sco[i][j].score=add[3];
			else if(sco[i][j].die3>=1)
				sco[i][j].score=add[4];
			else if(sco[i][j].alive2>=1)
				sco[i][j].score=add[5];
			else if(sco[i][j].die2>=1)
				sco[i][j].score=add[6];
			else if(sco[i][j].alive1>=1)
				sco[i][j].score=add[7];
			else if(sco[i][j].die1>=2)
				sco[i][j].score=add[8];
			else
				sco[i][j].score=0;
		}
	}
}

//游戏主逻辑：鼠标事件标记；q键结束游戏；玩家执黑棋先行，AI执白棋后行；判断游戏状态
void game_start()
{
	int i;
	FlushMouseMsgBuffer();		//先清除鼠标缓存
	MOUSEMSG mvalue;			//鼠标标记
	while(1)					//主程序一直循环
	{
		FlushMouseMsgBuffer();
		//游戏是否结束判断
		if(_kbhit())
		{
			char ch=_getch();
			if(ch=='q')
			{
				printf("游戏已结束\n");
				exit(0);
			}
		}
		clue_print(playturn);
		mvalue=GetMouseMsg();
		Point pselect;
		switch(mvalue.uMsg)
		{
		case WM_MOUSEMOVE:
			for(i=0;i<255;i++)
			{
				if((mvalue.x>=cursor[i].pointx-15&&mvalue.x<=cursor[i].pointx+15)&&(mvalue.y>=cursor[i].pointy-15&&mvalue.y<=cursor[i].pointy+15))
				{
					pselect=cursor[i];
				}
			}
			break;
		case WM_LBUTTONUP:
			if(getpixel(pselect.pointx,pselect.pointy)==RGB(0,0,0))	break;
			if(getpixel(pselect.pointx,pselect.pointy)==RGB(255,255,255))	break;
			player[playturn]=pselect;
			maps[(pselect.pointy-25)/30][(pselect.pointx-50)/30]=playturn%2;
			setfillcolor(BLACK);
			setlinestyle(PS_SOLID);
			fillcircle(pselect.pointx,pselect.pointy,10);
			judge(playturn%2);		//判断棋局
			playturn+=1;
			clue_print(playturn);
			Sleep(1000);
			pselect = AIPlay();
			maps[(pselect.pointy-25)/30][(pselect.pointx-50)/30]=playturn%2;
			setfillcolor(WHITE);
			setlinestyle(PS_SOLID);
			fillcircle(pselect.pointx,pselect.pointy,10);
			judge(playturn%2);		//判断棋局
			playturn+=1;
			break;
		}
	}
}


int main()
{
	initgraph(520, 520);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "五子棋小游戏");
	game_init();
	system("pause");
	return 0;
}


