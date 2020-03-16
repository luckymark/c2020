#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define For(x,a,b) for(x=a;x<=b;x++)
int i,i1,i2;
int main(void)
{
	//载入地图。空白为0，─为1，|为2，入口为3，出口为4。玩家设定为88。
	//设定制表符：┎=5,┒=6,┖=7,┚=8,├=9,┤=10,┴=11,┬=12. 
	int maze[23][23]={
	{5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6},
	{2,0,0,0,2,0,0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,2},
	{2,0,1,1,8,0,1,1,1,1,8,0,2,0,1,1,1,1,12,1,1,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,2},
	{9,1,6,0,5,1,1,1,1,1,1,1,11,1,1,1,6,0,2,0,1,1,10},
	{2,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,2},
	{2,0,2,0,2,0,5,1,1,1,1,1,1,1,1,0,9,1,11,1,6,0,2},
	{2,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,2},
	{2,0,7,1,6,0,2,0,2,0,5,1,12,1,1,0,9,1,1,0,2,0,2},
	{2,0,0,0,2,0,2,0,2,0,2,0,2,0,0,0,2,0,0,0,2,0,2},
	{2,0,2,0,2,0,2,0,2,0,2,0,2,0,5,1,8,0,1,1,10,0,2},
	{2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,0,0,0,0,2,0,2},
	{2,0,2,0,2,0,9,1,11,1,8,0,7,1,8,0,5,1,1,1,10,0,2},
	{2,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,2},
	{2,0,2,0,5,1,10,0,2,0,5,1,1,0,5,1,8,0,2,0,2,0,2},
	{3,0,2,0,2,0,2,0,2,0,2,0,0,0,2,0,0,0,2,0,0,0,4},//出入口位于此行，第16行 
	{5,1,8,0,2,0,2,0,2,0,7,1,1,1,10,0,2,0,7,1,1,1,6},
	{2,0,0,0,2,0,2,0,2,0,0,0,0,0,2,0,2,0,0,0,0,0,2},
	{2,0,2,0,2,0,7,1,11,1,1,1,6,0,2,0,2,0,5,1,1,0,2},
	{2,0,2,0,0,0,0,0,0,0,0,0,2,0,2,0,2,0,2,0,0,0,2},
	{2,0,7,1,1,1,6,0,1,1,6,0,2,0,2,0,2,0,7,1,1,1,10},
	{2,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,2},
	{7,1,1,1,1,1,11,1,1,1,11,1,1,1,1,1,11,1,1,1,1,1,8}
	};
	int former,x,y;
	clock_t start,finish;
	double duration;
	long int count;//万一……我是说万一，是傻子玩这个极其简单的游戏胡乱按怎么办……?给足够空间防止计数器失灵吧。 
	char empty,direction;
	x=15;
	y=count=0;
	start=clock();
	while(x!=15||y!=22){
		system("CLS");
		printf("这是一个迷宫小游戏。请使用方向键（↑↓←→）进行控制。\n");
		printf("“E”是入口位置，“O”是出口位置，M是您当前的位置。\n"); 
		former=maze[x][y];//former用于存放玩家位置处的数字。 
		maze[x][y]=88;//设定玩家位置
		For(i1,0,22){
			For(i2,0,22){
//				switch(maze[i1][i2]){//加载地形 			//此方法失败了啊啊啊啊输出了一堆烂摊子！
//					case 0: printf(" "); break;				//保留以记录我的失败。
//					case 1: printf("-"); break;
//					case 2: printf("|"); break;
//					case 3: printf("E"); break;
//					case 4: printf("O"); break;
//					case 5: printf("┌"); break;
//					case 6: printf("┐"); break;
//					case 7: printf("└"); break;
//					case 8: printf("┘"); break;
//					case 9: printf("├"); break;
//					case 10: printf("┤"); break;
//					case 11: printf("┴"); break;
//					case 12: printf("┬"); break;
//					case 88: printf("★"); break;
//				}
				switch(maze[i1][i2]){//加载地形  
					case 0: printf(" "); break;	 
					case 1: printf("-"); break;
					case 2: printf("|"); break;
					case 3: printf("E"); break;
					case 4: printf("O"); break;
					case 5: printf("."); break;
					case 6: printf("."); break;
					case 7: printf("."); break;
					case 8: printf("."); break;
					case 9: printf("."); break;
					case 10: printf("."); break;
					case 11: printf("."); break;
					case 12: printf("."); break;
					case 88: printf("M"); break;
				}
			}
			printf("\n");
		}
		maze[x][y]=former;
		printf("您已经走了%d步。\n",count);//功能完善——步数统计 
		empty=getch(); 
		direction=getch();//方向键需要使用两个字符才能读入。因为在Windows下，方向键由两个字节组成，分别为:'\244'和'\72'up,'\80'down,'\75'left,'\77'right.
		switch(direction){//玩家进行移动 
			case 72: if(maze[x-1][y]==0){x-=1; count++;} break;//up
			case 80: if(maze[x+1][y]==0){x+=1; count++;} break;//down
			case 77: if(maze[x][y+1]==0||maze[x][y+1]==4){y+=1; count++;} break;//right
			case 75: if(maze[x][y-1]==0&&y!=0){y-=1; count++;} break;//left
		}
	}
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("恭喜您成功走出迷宫。\n您一共走了%d步，用时%.4f秒。\n",count,duration);
	system("pause");
	return 0;
}
