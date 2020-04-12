#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#define up 72
#define down 80
#define left 75
#define right 77
#define blank 0
#define wall 1
#define box 2
#define you 3 
#define goal 4
const int N=31,M=31,maxnum_maps=21;//地图最大行数+1，最大列数+1，地图最大张数+1
int totmaps=20,nowlevel=1;//总共地图数，现在的等级 
int nowx,nowy,cnt;//人现在所处的位置，步数计数器 
char str[105];//录入地图时用 
int map[maxnum_maps][N][M],size[maxnum_maps][2],totgoals[maxnum_maps];//各个等级的地图，每张地图的尺寸 ,每张地图的目标数 
int isgoal[maxnum_maps][N][M];//记录每张地图各个位置是否是目标点 
FILE *fp1,*fp2;//地图文件，等级文件 
void getmap()//读入地图 
{
	int nowrow=0;
	while(fgets(str,105,fp1)!=NULL&&strlen(str)>1)
	{
		nowrow++;//++后为现在的行下标 
		int len=strlen(str);len--;//去掉最后一个'\n' 
		size[nowlevel][1]=len;
		for(int i=0;i<len;i++)
		{
			switch(str[i])
			{
				case ' ':
					map[nowlevel][nowrow][i+1]=blank;break;
				case '*':
					map[nowlevel][nowrow][i+1]=wall;break;
				case 'G':
					map[nowlevel][nowrow][i+1]=goal;isgoal[nowlevel][nowrow][i+1]=1;totgoals[nowlevel]++;break;//同时记录该点是否是目标点 
				case 'B':
					map[nowlevel][nowrow][i+1]=box;break;
				case 'H':
					map[nowlevel][nowrow][i+1]=you;nowx=nowrow;nowy=i+1;break;//同时获取人的起始位置 
				case 'h'://初始人踩在一个goal上
					map[nowlevel][nowrow][i+1]=you;nowx=nowrow;nowy=i+1;
					isgoal[nowlevel][nowrow][i+1]=1;totgoals[nowlevel]++;
					break;
				case 'b'://初始箱子压在一个goal上 
					map[nowlevel][nowrow][i+1]=box;isgoal[nowlevel][nowrow][i+1]=1;totgoals[nowlevel]++;break;
			}
		}
	}
	size[nowlevel][0]=nowrow;
}
void print()
{
	for(int i=1;i<=size[nowlevel][0];i++)
	{
		for(int j=1;j<=size[nowlevel][1];j++)
		{
			int nowpos=map[nowlevel][i][j];
			if(nowpos==blank) printf("  ");
			else if(nowpos==wall) printf("■");
			else if(nowpos==box) printf("箱");
			else if(nowpos==goal) printf("!!");
			else printf("你");
		}
		printf("\n");
	}
	printf("\n请使用方向键操作\n当前步数：%d\n\n成绩在\"your socre.txt\"里",cnt);
}
void play_game()
{
	while(nowlevel<=totmaps)//如果现在的等级不超过总地图数，则进行当前等级的地图的游戏 
	{
		getmap();//获取当前等级的地图
		cnt=0;//初始化步数 
		print();
		int c1,c2,goalsdown=0;//goalsdown表示当前完成的目标数 
		while(goalsdown<totgoals[nowlevel])
		{
			c1=getch();c2=getch();
			if(c1!=224&&c2!=224) continue;
			if(c1!=224&&c2==224) c2=getch();//保证即使在按了其他键后也能正常进行 
			int nextx,nexty;
			switch(c2)
			{
				case up:
					nextx=nowx-1;nexty=nowy;break;
				case down:
					nextx=nowx+1;nexty=nowy;break;
				case left:
					nextx=nowx;nexty=nowy-1;break;
				case right:
					nextx=nowx;nexty=nowy+1;break;
				default:
					continue;
			}
			int nextpos=map[nowlevel][nextx][nexty];
			if(nextpos==wall) continue;//不能走到墙上去，因为地图是用墙围起来的，所以不用担心走到地图外面去 
			if(nextpos==box)//如果要推一个箱子 
			{
				int nnextx=2*nextx-nowx,nnexty=2*nexty-nowy;
				int nnextpos=map[nowlevel][nnextx][nnexty];//如果推了箱子，箱子的位置
				if(nnextpos==wall||nnextpos==box) continue;//不能将箱子推到墙上或另一个箱子上 
				//成功推出箱子 
				map[nowlevel][nnextx][nnexty]=box;
				if(isgoal[nowlevel][nnextx][nnexty]) goalsdown++;//如果将箱子推上了一个目标 ，则goalsdown++ 
				if(isgoal[nowlevel][nextx][nexty]) goalsdown--;//如果将箱子推离了一个目标，则goalsdown-- 
			}
			//自己的移动 
			map[nowlevel][nextx][nexty]=you;
			map[nowlevel][nowx][nowy]=isgoal[nowlevel][nowx][nowy]?goal:blank;
			nowx=nextx;nowy=nexty;
			cnt++;
			system("cls");
			print();
		}
		system("cls");
		fprintf(fp2,"level %d的总步数：%d\n\n",nowlevel,cnt);
		nowlevel++;
	}
	printf("\nORZ!!\n\n"); 
}
int main()
{
	fp1=fopen("map.txt","r");
	fp2=fopen("your score.txt","w");
	if(fp1==NULL) printf("读取地图失败，请将\"map.txt\"置于程序处，然后重新运行程序。");
	else play_game();
	return 0;
}
