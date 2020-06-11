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
#define min(x,y) (x>y?y:x)
#define max(x,y) (x>y?x:y)
const int LEN=15;
const int LAYER=2;
const int MAXN=LEN+2;
const int INF=1e9;
const int MAXDIFF=3;
const int MAXSAME=6;
const int MAXSPACE=4;
const int MATCHES=8;
char title[30]="title Gobang  OmegaGO ver2.0";
int value[MAXN][MAXN],init[MAXN][MAXN],stx[MAXN*MAXN],sty[MAXN*MAXN],sco[MAXSAME][MAXDIFF][MAXSPACE];
int top=0,mx[MAXN],rx[MAXN],ry[MAXN],randsco[MAXSAME][MAXDIFF][MAXSPACE],cntwin,cntlose;
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
	srand(time(NULL));
	FILE *fp=fopen("parameter.txt","r");
	for(int i=1;i<MAXSAME;i++)for(int j=0;j<MAXDIFF;j++)for(int k=0;k<MAXSPACE;k++)fscanf(fp,"%d",&sco[i][j][k]); 
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
		printf("©¦                  OmegaGo ver2.0                  ©¦\n");
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
	if(sco[0][0][0])printf("%d %d\n",cntwin,cntlose);
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
inline int val(int same,int diff,int space,int type)
{
	if(type==1)return sco[min(same,MAXSAME-1)][diff][min(space,MAXSPACE-1)];
	else return randsco[min(same,MAXSAME-1)][diff][min(space,MAXSPACE-1)];
}
int cal(int type)
{
	int ret=0,cntsame=0,cntspace=0,cntdiff=0;
	for(int i=1;i<=LEN;i++)
	{
		for(int j=1;j<=LEN;j++)
	 	{
	 		if(value[i][j]==9)
	 		{
	 			cntsame=1,cntspace=0,cntdiff=0;
	 			for(int k=i+1;k<=min(LEN,i+4);k++)
	 			{
	 				if(value[k][j]==10){cntdiff++;break;}
	 				if(value[k][j]==9)cntsame++;
	 				else cntspace++;
				}
				for(int k=i-1;k>=max(1,i-4);k--)
				{
	 				if(value[k][j]==10){cntdiff++;break;}
	 				if(value[k][j]==9)cntsame++;
	 				else cntspace++;
				}
				ret+=val(cntsame,cntdiff,cntspace,type);
	 			cntsame=1,cntspace=0,cntdiff=0;
	 			for(int k=j+1;k<=min(LEN,j+4);k++)
	 			{
	 				if(value[i][k]==10){cntdiff++;break;}
	 				if(value[i][k]==9)cntsame++;
	 				else cntspace++;
				}
				for(int k=j-1;k>=max(1,j-4);k--)
				{
	 				if(value[i][k]==10){cntdiff++;break;}
	 				if(value[i][k]==9)cntsame++;
	 				else cntspace++;					
				}
				ret+=val(cntsame,cntdiff,cntspace,type);
				cntsame=1,cntspace=0,cntdiff=0;
				for(int k=1;k<=min(4,min(LEN-i,LEN-j));k++)
				{
					if(value[i+k][j+k]==10){cntdiff++;break;}
	 				if(value[i+k][j+k]==9)cntsame++;
	 				else cntspace++;
				}
				for(int k=-1;k>=max(-4,max(1-i,1-j));k--)
				{
	 				if(value[i+k][j+k]==10){cntdiff++;break;}
	 				if(value[i+k][j+k]==9)cntsame++;
	 				else cntspace++;					
				}
				ret+=val(cntsame,cntdiff,cntspace,type);
				cntsame=1,cntspace=0,cntdiff=0;
				for(int k=1;k<=min(4,min(LEN-i,j-1));k++)
				{
					if(value[i+k][j-k]==10){cntdiff++;break;}
	 				if(value[i+k][j-k]==9)cntsame++;
	 				else cntspace++;
				}
				for(int k=-1;k>=max(-4,max(1-i,j-LEN));k--)
				{
	 				if(value[i+k][j-k]==10){cntdiff++;break;}
	 				if(value[i+k][j-k]==9)cntsame++;
	 				else cntspace++;					
				}
				ret+=val(cntsame,cntdiff,cntspace,type);
			}
			if(value[i][j]==10)
			{
	 			cntsame=1,cntspace=0,cntdiff=0;
	 			for(int k=i+1;k<=min(LEN,i+4);k++)
	 			{
	 				if(value[k][j]==9){cntdiff++;break;}
	 				if(value[k][j]==10)cntsame++;
	 				else cntspace++;
				}
				for(int k=i-1;k>=max(1,i-4);k--)
				{
	 				if(value[k][j]==9){cntdiff++;break;}
	 				if(value[k][j]==10)cntsame++;
	 				else cntspace++;
				}
				ret-=val(cntsame,cntdiff,cntspace,type);
	 			cntsame=1,cntspace=0,cntdiff=0;
	 			for(int k=j+1;k<=min(LEN,j+4);k++)
	 			{
	 				if(value[i][k]==9){cntdiff++;break;}
	 				if(value[i][k]==10)cntsame++;
	 				else cntspace++;
				}
				for(int k=j-1;k>=max(1,j-4);k--)
				{
	 				if(value[i][k]==9){cntdiff++;break;}
	 				if(value[i][k]==10)cntsame++;
	 				else cntspace++;					
				}
				ret-=val(cntsame,cntdiff,cntspace,type);
				cntsame=1,cntspace=0,cntdiff=0;
				for(int k=1;k<=min(4,min(LEN-i,LEN-j));k++)
				{
					if(value[i+k][j+k]==9){cntdiff++;break;}
	 				if(value[i+k][j+k]==10)cntsame++;
	 				else cntspace++;
				}
				for(int k=-1;k>=max(-4,max(1-i,1-j));k--)
				{
	 				if(value[i+k][j+k]==9){cntdiff++;break;}
	 				if(value[i+k][j+k]==10)cntsame++;
	 				else cntspace++;					
				}
				ret-=val(cntsame,cntdiff,cntspace,type);
				cntsame=1,cntspace=0,cntdiff=0;
				for(int k=1;k<=min(4,min(LEN-i,j-1));k++)
				{
					if(value[i+k][j-k]==9){cntdiff++;break;}
	 				if(value[i+k][j-k]==10)cntsame++;
	 				else cntspace++;
				}
				for(int k=-1;k>=max(-4,max(1-i,j-LEN));k--)
				{
	 				if(value[i+k][j-k]==9){cntdiff++;break;}
	 				if(value[i+k][j-k]==10)cntsame++;
	 				else cntspace++;					
				}
				ret-=val(cntsame,cntdiff,cntspace,type);
			}
		}
	 }
	 return ret;
}
int dfs(int step,int player,int type)
{
	if(step%2)mx[step]=1e9;
	else mx[step]=-1e9;
	if(step==LAYER)
	{
		return cal(type);
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
								value[p][q]=9;
								int tmp=dfs(step+1,0,type);
								if(tmp>mx[step])
								{
									mx[step]=tmp;
									rx[step]=p;
									ry[step]=q;
								}
								if(tmp*2>=mx[step]&&(rand()%5==0))
								{
									rx[step]=p;
									ry[step]=q;
								}
							}
							if(player==0)
							{
								value[p][q]=10;
								int tmp=dfs(step+1,1,type);
								if(tmp<mx[step])
								{
									mx[step]=tmp;
									rx[step]=p;
									ry[step]=q;
								}
								if(tmp*2<=mx[step]&&(rand()%5==0))
								{
									rx[step]=p;
									ry[step]=q;
								}
							}
							value[p][q]=init[p][q];					
						}
					}
				}
			}
		}
	}
	return mx[step];
}
void robot(int type)
{
	dfs(0,1,type);
	printboard(ry[0],rx[0],type);
}
void single()
{
	system("pause>nul 2>nul");       
	system("cls");
	system ("mode con cols=43 lines=20");   
	system("color 3f");
	system(title);
	printf("©°¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©´\n");
	printf("©¦            OmegaGo ver2.0              ©¦\n");
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
						robot(1);
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
void train()
{
	system("pause>nul 2>nul");       
	system("cls");
	system ("mode con cols=43 lines=20");   
	system("color 3f");
	system(title);
	sco[0][0][0]=1; 
	while(1)
	{
		for(int i=1,up=35;i<MAXSAME;i++,up*=35)
			for(int j=0,t=up;j<MAXDIFF;j++,t/=4)
				for(int k=0,m=t;k<MAXSPACE;k++,m*=4,m/=5)
					randsco[i][j][k]=rand()*rand()%(m+1);
		cntwin=0,cntlose=0;
		for(int i=1;i<=MATCHES;i++)
		{
			int tot=0;
			empty();
			top=0;
			printboard(8,8,0);
			while(tot<LEN*LEN/3)
			{
				robot(1);
				tot++;
				if(win())
				{
					cntlose++;
					break;
				}
				robot(0);
				tot++;
				if(win())
				{
					cntwin++;
					break;
				}
			}
		}
		for(int i=1;i<=MATCHES;i++)
		{
			if(cntlose>=MATCHES)break;
			int tot=0;
			empty();
			top=0;
			printboard(8,8,1);
			while(tot<LEN*LEN/3)
			{
				robot(0);
				tot++;
				if(win())
				{
					cntwin++;
					break;
				}
				robot(1);
				tot++;
				if(win())
				{
					cntlose++;
					break;
				}
			}
		}
		if(cntwin>cntlose)
		{
			FILE *fp=fopen("parameter.txt","w");
			for(int i=1;i<MAXSAME;i++)
				for(int j=0;j<MAXDIFF;j++)
				{
					for(int k=0;k<MAXSPACE;k++)
						fprintf(fp,"%d ",sco[i][j][k]=sco[i][j][k]+(int)((randsco[i][j][k]-sco[i][j][k])*(((cntwin-cntlose)*1.0)/(1.0*(cntwin+cntlose)))));
					fprintf(fp,"\n");
				}
			fclose(fp);
		}
	}
} 
