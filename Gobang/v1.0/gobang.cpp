/*
4/18 2h30min menu+move_cursor+place_piece
5/26 4h00min retract+cal_val+check_win+dfs_without_prune+memorization
5/27 0h20min go_first/second
*/
#include<time.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<algorithm>
#define min(x,y) (x>y?y:x)
#define max(x,y) (x>y?x:y)
using namespace std;
const int LEN=15;
const int LAYER=2;
const int VALTYPE=6;
const int MAXN=LEN+2;
char title[30]="title Gobang  OmegaGO ver1.0";
int value[MAXN][MAXN],score[LAYER][MAXN][MAXN],init[MAXN][MAXN],stx[MAXN*MAXN],sty[MAXN*MAXN],sco[VALTYPE];
int top=0,mx[MAXN],rx[MAXN],ry[MAXN],randsco[VALTYPE];
char ch[11][4]={"©°","©Ð","©´","©À","©à","©È","©¸","©Ø","©¼","¡ñ","¡ð"};
void startgame();
void empty(); 
void single();
void train();
void introduce();
void about();
void Exit();
void mainmenu();
void victory();
void defeat();
void retract();
int position();
int win();
int cal();
void printboard(int *x,int *y,int player);
void multi();//
void robot();		
void chessone();
void chessscore();
void initialize(); 
inline bool check(int x,int y){return x<=15&&x>=1&&y<=15&&y>=1;}
int main()
{
	initialize();
	startgame();
	return 0;
}
void initialize()
{
	FILE *fp=fopen("parameter.txt","r");
	for(int i=0;i<VALTYPE;i++)fscanf(fp,"%d",&sco[i]); 
	fclose(fp);
	init[1][1]=0;init[1][LEN]=2;
	init[LEN][1]=6;init[LEN][LEN]=8;
	for(int i=2;i<LEN;i++)
	{
		init[1][i]=1,init[i][1]=3;
		init[LEN][i]=7,init[i][LEN]=5;
		for(int j=2;j<LEN;j++)
		{
			init[i][j]=4;
		}
	}
}
void startgame()
{
	empty();
	mainmenu();
}
void empty()
{
	for(int i=1;i<=LEN;i++)for(int j=1;j<=LEN;j++)value[i][j]=init[i][j];
}
void mainmenu()
{
	while(1)
	{
		system("cls");
		system(title);
		system("color 3f");
		system ("mode con cols=56 lines=20");
		printf("©°¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©´\n");
		printf("©¦                  OmegaGo ver1.0                  ©¦\n");
		printf("©¦[1] START                                         ©¦\n");
		printf("©¦                                                  ©¦\n");
		printf("©¦[2] TRAIN                                         ©¦\n");
		printf("©¦                                                  ©¦\n");
		printf("©¦[3] INTRODUCE                                     ©¦\n");
		printf("©¦                                                  ©¦\n");
		printf("©¦[4] ABOUT                                         ©¦\n");
		printf("©¦                                                  ©¦\n");
		printf("©¦[5] EXIT                                          ©¦\n");
		printf("©¸¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©¼\n");
		char tmp;
		while(tmp=getch())
		{
			switch(tmp)
			{
				case '1':single();break;
				case '2':train();break;
				case '3':introduce();break;
				case '4':about();break;
				case '5':Exit();break;//flag
				default:break;
			}
		}
	}
}
void introduce()
{
	
}
void about()
{
	
}
void Exit()
{
	exit(0);
}
void victory()
{
	puts("YOU WIN");
	Exit();
}
void defeat()
{
	puts("YOU LOSE");
	Exit();
}
int win()
{
	for(int i=1;i<=LEN;i++)
	{
		for(int j=1;j<=LEN;j++)
	 	{
	 		if(value[i][j]==9)
	 		{
	 			int tmpcnt=0;
	 			for(int k=max(1,i-4);k<=min(LEN,i+4);k++)
	 			{
	 				if(value[k][j]==9)
	 				{
						if(++tmpcnt==5)return 1;
					}
					else tmpcnt=0;
				}
				tmpcnt=0;
	 			for(int k=max(1,j-4);k<=min(LEN,j+4);k++)
	 			{
	 				if(value[i][k]==9)
	 				{
						if(++tmpcnt==5)return 1;
					}
					else tmpcnt=0;
				}
				tmpcnt=0;
				for(int k=max(-4,max(1-i,1-j));k<=min(4,min(LEN-i,LEN-j));k++)
				{
					if(value[i+k][j+k]==9)
					{
						if(++tmpcnt==5)return 1;
					}
					else tmpcnt=0;
				}
				tmpcnt=0;
				for(int k=max(-4,max(1-i,j-LEN));k<=min(4,min(LEN-i,j-1));k++)
				{
					if(value[i+k][j-k]==9)
					{
						if(++tmpcnt==5)return 1;
					}
					else tmpcnt=0;
				}
			}
			if(value[i][j]==10)
			{
	 			int tmpcnt=0;
	 			for(int k=max(1,i-4);k<=min(LEN,i+4);k++)
	 			{
	 				if(value[k][j]==10)
	 				{
						if(++tmpcnt==5)return 1;
					}
					else tmpcnt=0;
				}
				tmpcnt=0;
	 			for(int k=max(1,j-4);k<=min(LEN,j+4);k++)
	 			{
	 				if(value[i][k]==10)
	 				{
						if(++tmpcnt==5)return 1;
					}
					else tmpcnt=0;
				}
				tmpcnt=0;
				for(int k=max(-4,max(1-i,1-j));k<=min(4,min(LEN-i,LEN-j));k++)
				{
					if(value[i+k][j+k]==10)
					{
						if(++tmpcnt==5)return 1;
					}
					else tmpcnt=0;
				}
				tmpcnt=0;
				for(int k=max(-4,max(1-i,j-LEN));k<=min(4,min(LEN-i,j-1));k++)
				{
					if(value[i+k][j-k]==10)
					{
						if(++tmpcnt==5)return 1;
					}
					else tmpcnt=0;
				}
			}
		}
	 }
	 return 0;
}
void printboard(int y,int x,int player)
{
	system("cls");
	if(player==0||player==1)
	{
		if(player==0)
		{
			value[x][y]=10;
		}
		else if(player==1)
		{
			value[x][y]=9;
		}
		stx[++top]=x;
		sty[top]=y;
	}
	printf("     1 2 3 4 5 6 7 8 9 0 1 2 3 4 5\n");
	for(int i=1;i<=LEN;i++)
	{
		printf("    %d",i%10);
		for(int j=1;j<=LEN;j++)
		{
			printf("%s",ch[value[i][j]]);
			if(strcmp(ch[value[i][j]],"¡ð")!=0&&strcmp(ch[value[i][j]],"¡ñ")!=0)printf(" ");
		}
		puts("");
	}
}
void goto_xy(int x, int y)
{   
	system("cls");
    printboard(0,0,-1);
    x=2*x+3;
    y=y;
    HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos={x,y};
    SetConsoleCursorPosition(hOut, pos);
}
void retract()
{
	if(top>0)
	{
		value[stx[top]][sty[top]]=init[stx[top]][sty[top]];
		top--;
		value[stx[top]][sty[top]]=init[stx[top]][sty[top]];
		top--;
	}
}
int cal()
{
	int ret=0;
	for(int i=1;i<=LEN;i++)
	{
		for(int j=1;j<=LEN;j++)
	 	{
	 		if(value[i][j]==9)
	 		{
	 			int tmpcnt=0;
	 			for(int k=max(1,i-4);k<=min(LEN,i+4);k++)
	 			{
	 				if(value[k][j]==9)tmpcnt++;
	 				if(value[k][j]==10)ret+=sco[max(tmpcnt-1,1)],tmpcnt=0;
				}
				ret+=sco[tmpcnt];
				tmpcnt=0;
	 			for(int k=max(1,j-4);k<=min(LEN,j+4);k++)
	 			{
	 				if(value[i][k]==9)tmpcnt++;
	 				if(value[i][k]==10)ret+=sco[max(tmpcnt-1,1)],tmpcnt=0;
				}
				ret+=sco[tmpcnt];
				tmpcnt=0;
				for(int k=max(-4,max(1-i,1-j));k<=min(4,min(LEN-i,LEN-j));k++)
				{
					if(value[i+k][j+k]==9)tmpcnt++;
					if(value[i+k][j+k]==10)ret+=sco[max(tmpcnt-1,1)],tmpcnt=0;
				}
				ret+=sco[tmpcnt];
				tmpcnt=0;
				for(int k=max(-4,max(1-i,j-LEN));k<=min(4,min(LEN-i,j-1));k++)
				{
					if(value[i+k][j-k]==9)tmpcnt++;
					if(value[i+k][j-k]==10)ret+=sco[max(tmpcnt-1,1)],tmpcnt=0;
				}
				ret+=sco[tmpcnt];
				tmpcnt=0;
			}
			if(value[i][j]==10)
			{
				int tmpcnt=0;
	 			for(int k=max(1,i-4);k<=min(LEN,i+4);k++)
	 			{
	 				if(value[k][j]==10)tmpcnt++;
	 				if(value[k][j]==9)ret-=sco[max(tmpcnt-1,1)],tmpcnt=0;
				}
				ret-=sco[tmpcnt];
				tmpcnt=0;
	 			for(int k=max(1,j-4);k<=min(LEN,j+4);k++)
	 			{
	 				if(value[i][k]==10)tmpcnt++;
	 				if(value[i][k]==9)ret-=sco[max(tmpcnt-1,1)],tmpcnt=0;
				}
				ret-=sco[tmpcnt];
				tmpcnt=0;
				for(int k=max(-4,max(1-i,1-j));k<=min(4,min(LEN-i,LEN-j));k++)
				{
					if(value[i+k][j+k]==10)tmpcnt++;
					if(value[i+k][j+k]==9)ret-=sco[max(tmpcnt-1,1)],tmpcnt=0;
				}
				ret-=sco[tmpcnt];
				tmpcnt=0;
				for(int k=max(-4,max(1-i,j-LEN));k<=min(4,min(LEN-i,j-1));k++)
				{
					if(value[i+k][j-k]==10)tmpcnt++;
					if(value[i+k][j-k]==9)ret-=sco[max(tmpcnt-1,1)],tmpcnt=0;
				}
				ret-=sco[tmpcnt];
				tmpcnt=0;
			}
		}
	 }
	 return ret;
}
int dfs(int step,int player)
{
	if(step%2)mx[step]=1e9;
	else mx[step]=-1e9;
	if(step==LAYER)
	{
		return cal();
	}
	for(int i=1;i<=LEN;i++)
	{
		for(int j=1;j<=LEN;j++)
		{
			if(value[i][j]==9||value[i][j]==10)
			{
				for(int p=max(1,i-1);p<=min(LEN,i+1);p++)
				{
					for(int q=max(1,j-1);q<=min(LEN,j+1);q++)
					{
						if(value[p][q]!=9&&value[p][q]!=10)
						{
							if(player==1)
							{
								if(score[step][p][q]!=0xc0c0c0c0)continue;/////////////////
								value[p][q]=9;
								int tmp=dfs(step+1,0);
								if(tmp>mx[step])
								{
									mx[step]=tmp;
									rx[step]=p;
									ry[step]=q;
								}
								score[step][p][q]=tmp;
							}
							if(player==0)
							{
								if(score[step][p][q]!=0xc0c0c0c0)continue;
								value[p][q]=10;
								int tmp=dfs(step+1,1);
								if(tmp<mx[step])
								{
									mx[step]=tmp;
									rx[step]=p;
									ry[step]=q;
								}
								score[step][p][q]=tmp;
							}
							value[p][q]=init[p][q];					
						}
					}
				}
			}
		}
	}
	memset(score[step],0xc0,sizeof score[step]);
	return mx[step];
}
void robot()
{
	memset(score,0xc0,sizeof score);
	dfs(0,1);
	printboard(ry[0],rx[0],1);
}
void single()
{
	system("pause>nul 2>nul");       
	system("cls");
	system ("mode con cols=43 lines=20");   
	system("color 3f");
	system(title);
	printf("©°¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©´\n");
	printf("©¦            OmegaGo ver1.0              ©¦\n");
	printf("©¦[1] GO FIRST                            ©¦\n");
	printf("©¦                                        ©¦\n");
	printf("©¦[2] GO SECOND                           ©¦\n");
	printf("©¸¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©¼\n");
	top=0;char tmp=0,flag=1,nowx=8,nowy=8;
	while(tmp=getch())
	{
		if(tmp=='1')printboard(0,0,-1),flag=0;
		if(tmp=='2')printboard(8,8,1),flag=0;
		if(flag==0)break;
	}
	goto_xy(nowx,nowy);
	while(1)
	{
		while(tmp=getch())
		{
			switch(tmp)
			{
			    case 72:
					if(check(nowx,nowy-1))
						goto_xy(nowx,--nowy);
					break; 
			    case 80:
					if(check(nowx,nowy+1))
						goto_xy(nowx,++nowy);
					break; 
				case 75:
					if(check(nowx-1,nowy))
						goto_xy(--nowx,nowy);
					break; 
				case 77:
					if(check(nowx+1,nowy))
						goto_xy(++nowx,nowy);
					break; 
				case 32:
					if(!(value[nowy][nowx]==9||value[nowy][nowx]==10))
					{
						printboard(nowx,nowy,0);
						if(win())victory();
						robot();
						if(win())defeat();
					}
					break;
				case 8:
					retract();
					printboard(0,0,-1);
					break;
				default:break;
			}
		}
	}
}
