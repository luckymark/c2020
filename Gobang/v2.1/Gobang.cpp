/*
4/18 2h30min menu+move_cursor+place_piece
5/26 4h00min retract+cal_val+check_win+dfs_without_prune+memorization
5/27 5h20min go_first/second+update_cal_val+train 
5/28 2h30min alpha_beta_prune+update_cal_val
6/1  1h00min debug_dfs+update_parameters
*/
#include"Gobang.h"
void fread()
{
	FILE *fp=fopen("parameter_v2.1.txt","r");
	for(int i=1;i<MAXSAME;i++)for(int j=0;j<MAXDIFF;j++)for(int k=0;k<MAXSPACE;k++)fscanf(fp,"%d",&sco[i][j][k]); 
	fclose(fp);
} 
void initialize()
{
	srand(time(NULL));
	fread();
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
void empty()
{
	for(int i=1;i<=LEN;i++)for(int j=1;j<=LEN;j++)value[i][j]=init[i][j];
}
void victory()
{
	puts("\nYOU WIN");
	printf("Press any key to return to the mainmenu.              \n");
	getch();
	exit(0);
}
void defeat()
{
	puts("\nYOU LOSE");
	printf("Press any key to return to the mainmenu.              \n");
	getch();
	exit(0);
}
inline int val(int same,int diff,int space,int type)
{
	if(type==1)return sco[min(same,MAXSAME-1)][diff][min(space,MAXSPACE-1)];
	else return randsco[min(same,MAXSAME-1)][diff][min(space,MAXSPACE-1)];
}
int cal(int type)
{
	int ret=0,cntsame=0,cntspace=0,cntdiff=0,flag1=0,flag2=0;
	for(int i=1;i<=LEN;i++)
	{
		for(int j=1;j<=LEN;j++)
	 	{
	 		if(value[i][j]==9)
	 		{
	 			cntsame=1,cntspace=0,cntdiff=0,flag1=0,flag2=0;
	 			for(int k=i+1;k<=min(LEN,i+4);k++)
	 			{
	 				if(value[k][j]==10){cntdiff++;flag1=1;break;}
	 				if(value[k][j]==9)cntsame++;
	 				else cntspace++;
				}
				for(int k=i-1;k>=max(1,i-4);k--)
				{
	 				if(value[k][j]==10){cntdiff++;flag2=1;break;}
	 				if(value[k][j]==9)cntsame++;
	 				else cntspace++;
				}
				if(LEN<i+4&&flag1==0)cntdiff++;
				if(1>i-4&&flag2==0)cntdiff++;
				ret+=val(cntsame,cntdiff,cntspace,type);
	 			cntsame=1,cntspace=0,cntdiff=0,flag1=0,flag2=0;
	 			for(int k=j+1;k<=min(LEN,j+4);k++)
	 			{
	 				if(value[i][k]==10){cntdiff++;flag1=1;break;}
	 				if(value[i][k]==9)cntsame++;
	 				else cntspace++;
				}
				for(int k=j-1;k>=max(1,j-4);k--)
				{
	 				if(value[i][k]==10){cntdiff++;flag2=1;break;}
	 				if(value[i][k]==9)cntsame++;
	 				else cntspace++;					
				}
				if(LEN<j+4&&flag1==0)cntdiff++;
				if(1>j-4&&flag2==0)cntdiff++;
				ret+=val(cntsame,cntdiff,cntspace,type);
				cntsame=1,cntspace=0,cntdiff=0,flag1=0,flag2=0;
				for(int k=1;k<=min(4,min(LEN-i,LEN-j));k++)
				{
					if(value[i+k][j+k]==10){cntdiff++;flag1=1;break;}
	 				if(value[i+k][j+k]==9)cntsame++;
	 				else cntspace++;
				}
				for(int k=-1;k>=max(-4,max(1-i,1-j));k--)
				{
	 				if(value[i+k][j+k]==10){cntdiff++;flag2=1;break;}
	 				if(value[i+k][j+k]==9)cntsame++;
	 				else cntspace++;					
				}
				if(min(LEN-i,LEN-j)<4&&flag1==0)cntdiff++;
				if(max(1-i,1-j)>-4&&flag2==0)cntdiff++;
				ret+=val(cntsame,cntdiff,cntspace,type);
				cntsame=1,cntspace=0,cntdiff=0,flag1=0,flag2=0;
				for(int k=1;k<=min(4,min(LEN-i,j-1));k++)
				{
					if(value[i+k][j-k]==10){cntdiff++;flag1=1;break;}
	 				if(value[i+k][j-k]==9)cntsame++;
	 				else cntspace++;
				}
				for(int k=-1;k>=max(-4,max(1-i,j-LEN));k--)
				{
	 				if(value[i+k][j-k]==10){cntdiff++;flag2=1;break;}
	 				if(value[i+k][j-k]==9)cntsame++;
	 				else cntspace++;					
				}
				if(min(LEN-i,j-1)<4&&flag1==0)cntdiff++;
				if(max(1-i,j-LEN)>-4&&flag2==0)cntdiff++;
				ret+=val(cntsame,cntdiff,cntspace,type);
			}
			if(value[i][j]==10)
			{
	 			cntsame=1,cntspace=0,cntdiff=0,flag1=0,flag2=0;
	 			for(int k=i+1;k<=min(LEN,i+4);k++)
	 			{
	 				if(value[k][j]==9){cntdiff++;flag1=1;break;}
	 				if(value[k][j]==10)cntsame++;
	 				else cntspace++;
				}
				for(int k=i-1;k>=max(1,i-4);k--)
				{
	 				if(value[k][j]==9){cntdiff++;flag2=1;break;}
	 				if(value[k][j]==10)cntsame++;
	 				else cntspace++;
				}
				if(LEN<i+4&&flag1==0)cntdiff++;
				if(1>i-4&&flag2==0)cntdiff++;
				ret-=val(cntsame,cntdiff,cntspace,type);
	 			cntsame=1,cntspace=0,cntdiff=0,flag1=0,flag2=0;
	 			for(int k=j+1;k<=min(LEN,j+4);k++)
	 			{
	 				if(value[i][k]==9){cntdiff++;flag1=1;break;}
	 				if(value[i][k]==10)cntsame++;
	 				else cntspace++;
				}
				for(int k=j-1;k>=max(1,j-4);k--)
				{
	 				if(value[i][k]==9){cntdiff++;flag2=1;break;}
	 				if(value[i][k]==10)cntsame++;
	 				else cntspace++;					
				}
				if(LEN<j+4&&flag1==0)cntdiff++;
				if(1>j-4&&flag2==0)cntdiff++;
				ret-=val(cntsame,cntdiff,cntspace,type);
				cntsame=1,cntspace=0,cntdiff=0,flag1=0,flag2=0;
				for(int k=1;k<=min(4,min(LEN-i,LEN-j));k++)
				{
					if(value[i+k][j+k]==9){cntdiff++;flag1=1;break;}
	 				if(value[i+k][j+k]==10)cntsame++;
	 				else cntspace++;
				}
				for(int k=-1;k>=max(-4,max(1-i,1-j));k--)
				{
	 				if(value[i+k][j+k]==9){cntdiff++;flag2=1;break;}
	 				if(value[i+k][j+k]==10)cntsame++;
	 				else cntspace++;					
				}
				if(min(LEN-i,LEN-j)<4&&flag1==0)cntdiff++;
				if(max(1-i,1-j)>-4&&flag2==0)cntdiff++;
				ret-=val(cntsame,cntdiff,cntspace,type);
				cntsame=1,cntspace=0,cntdiff=0,flag1=0,flag2=0;
				for(int k=1;k<=min(4,min(LEN-i,j-1));k++)
				{
					if(value[i+k][j-k]==9){cntdiff++;flag1=1;break;}
	 				if(value[i+k][j-k]==10)cntsame++;
	 				else cntspace++;
				}
				for(int k=-1;k>=max(-4,max(1-i,j-LEN));k--)
				{
	 				if(value[i+k][j-k]==9){cntdiff++;flag2=1;break;}
	 				if(value[i+k][j-k]==10)cntsame++;
	 				else cntspace++;					
				}
				if(min(LEN-i,j-1)<4&&flag1==0)cntdiff++;
				if(max(1-i,j-LEN)>-4&&flag2==0)cntdiff++;
				ret-=val(cntsame,cntdiff,cntspace,type);
			}
		}
	 }
	 return ret;
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
	if(sco[0][0][0])mxcal0=min(mxcal0,cal(0));
	if(sco[0][0][0])mxcal1=max(mxcal1,cal(1));
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
	if(sco[0][0][0])printf("totwin:%d totlose:%d\ncal(0):%d cal(1):%d\ncntwin:%d cntlose:%d\n",totwin,totlose,cal(0),cal(1),cntwin,cntlose);
	printf("The last piece was put in:(%d %d)",x,y);
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
void goto_xy(int x,int y)
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
int dfs(int step,int player,int alpha,int beta,int type,int lastx,int lasty)
{
	if(win())
	{
		return player?-(LAYER-step+1)*INF:(LAYER-step+1)*INF;
	}
	memset(vis[step],0,sizeof vis[step]); 
	if(step%2)mx[step]=4*INF;
	else mx[step]=-4*INF;
	if(step==LAYER)
	{
		return cal(type);
	}
	for(int p=max(1,lastx-1);p<=min(LEN,lastx+1);p++)
	{
		for(int q=max(1,lasty-1);q<=min(LEN,lasty+1);q++)
		{
			if(value[p][q]==9||value[p][q]==10)continue;
			vis[step][p][q]=1;
			if(player==1)
			{
				value[p][q]=9;
				int tmp=dfs(step+1,0,alpha,beta,type,p,q);
//				printboard(q,p,player);
				value[p][q]=init[p][q];					
				if(tmp>mx[step])
				{
					alpha=tmp;
					mx[step]=tmp;
					rx[step]=p;
					ry[step]=q;
				}
				if(tmp>0)tmp=tmp*5/4;
				else tmp=tmp*4/5;
				if(sco[0][0][0]&&tmp>=mx[step]&&(rand()%10==0))
				{
					rx[step]=p;
					ry[step]=q;
				}
				if(alpha>=beta)return alpha;
			}
			if(player==0)
			{
				value[p][q]=10;
				int tmp=dfs(step+1,1,alpha,beta,type,p,q);
//				printboard(q,p,player);
				value[p][q]=init[p][q];					
				if(tmp<mx[step])
				{
					beta=tmp;
					mx[step]=tmp;
					rx[step]=p;
					ry[step]=q;
				}
				if(tmp>0)tmp=tmp*4/5;
				else tmp=tmp*5/4;
				if(sco[0][0][0]&&tmp<=mx[step]&&(rand()%10==0))
				{
					rx[step]=p;
					ry[step]=q;
				}
				if(alpha>=beta)return beta;
			}
		}
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
						if(value[p][q]==9||value[p][q]==10)continue;
						if(vis[step][p][q])continue; 
						vis[step][p][q]=1;
						if(player==1)
						{
							value[p][q]=9;
							int tmp=dfs(step+1,0,alpha,beta,type,p,q);
//				printboard(q,p,player);
							value[p][q]=init[p][q];					
							if(tmp>mx[step])
							{
								alpha=tmp;
								mx[step]=tmp;
								rx[step]=p;
								ry[step]=q;
							}
							if(tmp>0)tmp=tmp*5/4;
							else tmp=tmp*4/5;
							if(sco[0][0][0]&&tmp>=mx[step]&&(rand()%10==0))
							{
								rx[step]=p;
								ry[step]=q;
							}
							if(alpha>=beta)return alpha;
						}
						if(player==0)
						{
							value[p][q]=10;
							int tmp=dfs(step+1,1,alpha,beta,type,p,q);
//				printboard(q,p,player);
							value[p][q]=init[p][q];					
							if(tmp<mx[step])
							{
								beta=tmp;
								mx[step]=tmp;
								rx[step]=p;
								ry[step]=q;
							}
							if(tmp>0)tmp=tmp*4/5;
							else tmp=tmp*5/4;
							if(sco[0][0][0]&&tmp<=mx[step]&&(rand()%10==0))
							{
								rx[step]=p;
								ry[step]=q;
							}
							if(alpha>=beta)return beta;
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
	dfs(0,1,-INF,INF,type,stx[top],sty[top]);
	printboard(ry[0],rx[0],type);
}
inline bool check(int x,int y)
{
	return x<=15&&x>=1&&y<=15&&y>=1;
}
void single()
{
	system("pause>nul 2>nul");       
	system("cls");
	system ("mode con cols=43 lines=20");   
	system("color 3f");
	system(title);
	printf("©°¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©´\n");
	printf("©¦            OmegaGo ver2.1              ©¦\n");
	printf("©¦[1] GO FIRST                            ©¦\n");
	printf("©¦                                        ©¦\n");
	printf("©¦[2] GO SECOND                           ©¦\n");
	printf("©¦                                        ©¦\n");
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
		fread();
		for(int i=1,up=20;i<MAXSAME;i++,up*=20)
			for(int j=0,t=up;j<MAXDIFF;j++,t/=2)
				for(int k=0,m=t;k<MAXSPACE;k++)
					randsco[i][j][k]=(int)(0.7*(rand()*rand()%(m+1))+0.3*(sco[i][j][k]));
		for(int j=0;j<MAXDIFF;j++)for(int k=0;k<MAXSPACE;k++)randsco[5][j][k]=INF;
		for(int i=1;i<MAXSAME;i++)for(int k=0;k<=MAXSPACE-i;k++)randsco[i][2][k]=0;
		for(int i=1;i<MAXSAME;i++)randsco[i][0][0]=0,randsco[i][0][1]=0,randsco[i][1][0]=0;
		cntwin=0,cntlose=0;
		for(int i=1;i<=MATCHES;i++)
		{
			if(cntlose-cntwin>=MATCHES/2)
			{
				cntlose=MATCHES; 
				break;
			}
			int tot=0;
			empty();
			top=0;
			printboard(8,8,0);
			while(tot<MAXTOP)
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
			while(tot<MAXTOP)
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
			totwin++;
			FILE *fp=fopen("parameter_v2.1.txt","w");
			for(int i=1;i<MAXSAME;i++)
				for(int j=0;j<MAXDIFF;j++)
				{
					for(int k=0;k<MAXSPACE;k++)
						fprintf(fp,"%d ",sco[i][j][k]+(int)((randsco[i][j][k]-sco[i][j][k])*(((cntwin-cntlose)*1.0)/(1.0*(cntwin+cntlose)))));
					fprintf(fp,"\n");
				}
			fclose(fp);
		}
		else totlose++; 
	}
}
void mainmenu()
{
	while(1)
	{
		system("cls");
		system(title);
		system("color 3f");
		system ("mode con cols=43 lines=20"); 
		printf("©°¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©´\n");
		printf("©¦             OmegaGo ver2.1             ©¦\n");
		printf("©¦[1] START                               ©¦\n");
		printf("©¦                                        ©¦\n");
		printf("©¦[2] TRAIN                               ©¦\n");
		printf("©¦                                        ©¦\n");
		printf("©¦[3] INTRODUCE                           ©¦\n");
		printf("©¦                                        ©¦\n");
		printf("©¦[4] EXIT                                ©¦\n");
		printf("©¦                                        ©¦\n");
		printf("©¸¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©¼\n");
		char tmp;
		while(tmp=getch())
		{
			switch(tmp)
			{
				case '1':single();break;
				case '2':train();break;
				case '3':introduce();break;
				case '4':exit(0);break;//flag       
				default:break;
			}
		}
	}
}
void introduce()
{
	system("cls");
	printf("©°¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©´\n");
	printf("©¦                   Gobang Ver2.1                  ©¦\n");
	printf("©¦                                                  ©¦\n");
	printf("©¦Use the arrow keys to move the cursor.            ©¦\n");
	printf("©¦                                                  ©¦\n");
	printf("©¦Use the space bar to place a piece.               ©¦\n");
	printf("©¦                                                  ©¦\n");
	printf("©¦Use the backspace key to retract.                 ©¦\n");
	printf("©¦                                                  ©¦\n");
	printf("©¦The Gobang AI can train itself.                   ©¦\n");
	printf("©¦                                                  ©¦\n");
	printf("©¦Press any key to return to the mainmenu.          ©¦\n");
	printf("©¦                                                  ©¦\n");
	printf("©¸¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©¼\n");
	getch();
	mainmenu();
	return;
}
void startgame()
{
	empty();
	mainmenu();
}
int main()
{
	initialize();
	startgame();
	return 0;
} 
