#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#define For(x,a,b) for(x=a;x<=b;x++)
int i,i1,i2;
int main(void)
{
	start://将goto设置于此，以进行游戏的重新开始以及关卡重新选择。 
	int map[251][251],mapbackup[251][251];//定义一个大地图，到时候用来从文件读入地图（懒得使用而且没必要使用动态分配了，浪费就浪费吧QAQ） 
	int choice,width,length,number,former,x,y,flag,k,min;
	int xx[30],yy[30],type[30];//type是箱子类型，即是圆的还是方的。2是圆形，3是三角形，4是倒三角。xx和yy是箱子归宿的位置。 
	long int count,hour;//万一……我是说万一，是傻子玩这个游戏，胡乱按怎么办……?给足够空间防止计数器失灵吧。
	char xeon,direction,next,container;
	char user[865];//增加记录用户名功能，顺便致敬Qualcomm Snapdragon 865 
	clock_t start,finish;
	double duration;
	duration=0.0;//您的好友计时菌已上线 
	count=k=min=hour=0;//您的好友超级准确的计数菌已上线，小时和分钟菌整装待发！ 
	FILE *fp, *grd;//打开文件专用 
	printf("这是一个多关卡的推箱子游戏。请选择您要游玩的关卡或退出：\n");
	printf("0.退出   1.门外汉   2.新手   3.平均   4.熟练者   5.老手   6.专家   7.专业   8.所向披靡\n");
	scanf("%d",&choice);
	scanf("%c",&container);//这里的作用挺奇怪的，完全就是个替罪羊，因为输入数字以后的回车会直接被认为是user输入完毕了，所以要找个东西承载这个回车
	switch(choice){//罗里吧嗦的写好了一堆选择操作，同时设置检查防止出现文件打开错误的情况。 
		case 0: printf("欢迎随时再来挑战。\nNever Settle.\n"); exit(0);
		case 1: if((fp=fopen("map-1.txt","r"))==NULL){printf("打开游戏地图所在文件错误。请重试。\n"); exit(0);} break;
		case 2: if((fp=fopen("map-2.txt","r"))==NULL){printf("打开游戏地图所在文件错误。请重试。\n"); exit(0);} break;
		case 3: if((fp=fopen("map-3.txt","r"))==NULL){printf("打开游戏地图所在文件错误。请重试。\n"); exit(0);} break;
		case 4: if((fp=fopen("map-4.txt","r"))==NULL){printf("打开游戏地图所在文件错误。请重试。\n"); exit(0);} break;
		case 5: if((fp=fopen("map-5.txt","r"))==NULL){printf("打开游戏地图所在文件错误。请重试。\n"); exit(0);} break;
		case 6: if((fp=fopen("map-6.txt","r"))==NULL){printf("打开游戏地图所在文件错误。请重试。\n"); exit(0);} break;
		case 7: if((fp=fopen("map-7.txt","r"))==NULL){printf("打开游戏地图所在文件错误。请重试。\n"); exit(0);} break;
		case 8: if((fp=fopen("map-8.txt","r"))==NULL){printf("打开游戏地图所在文件错误。请重试。\n"); exit(0);} break;
		default: printf("选择出现错误。请重试。\n"); exit(0);
	}
	printf("请输入您的用户名：\n");
	while((user[k]=getchar())!='\n')k++;
	user[k]='\0';
	fscanf(fp,"%d  %d  %d  %d  %d",&width,&length,&number,&x,&y);//width是地图的宽度，length是地图的长度，number是箱子的个数，x与y是玩家重生点坐标。
	For(i,1,number){
		fscanf(fp,"%d  %d  %d",&xx[i+1],&yy[i+1],&type[i+1]);//读取箱子的坐标与类型 
	}
	for(i1=0;i1<width;i1++){
		for(i2=0;i2<length;i2++){
			fscanf(fp,"%d",&map[i1][i2]);
		}
	}
	for(i1=0;i1<width;i1++){
		for(i2=0;i2<length;i2++){//地图的无箱子备份版 
			if(map[i1][i2]==52||map[i1][i2]==53||map[i1][i2]==54) mapbackup[i1][i2]=0;
			else mapbackup[i1][i2]=map[i1][i2];
		}
	}
	if(fclose(fp)){//关闭地图文件，同时设置检查防止出现文件关闭错误的情况。
		printf("关闭文件出现错误。游戏即将退出。\n");
		exit(0);
	}
	start=clock();
	flag=0;
	while(flag==0){
		system("CLS");
		printf("“★”是您当前的位置，“■”是墙。除此之外的实心图形为您要推动的箱子，相应空心图形为您要推到的位置。\n");
		printf("请使用方向键（↑↓←→）进行控制。\n");
		former=map[x][y];//former用于存放玩家位置处的数字。
		map[x][y]=88;//设定玩家位置
		for(i1=0;i1<width;i1++){//加载地形
			for(i2=0;i2<length;i2++){
				switch(map[i1][i2]){
					case 0: printf("  "); break;//空地 
					case 1: printf("■"); break;//墙 
					case 2: printf("○"); break;//箱子一号与对应归宿（箱子是两位数，归宿是一位数） 
					case 52: printf("●"); break;
					case 3: printf("△"); break;//箱子二号与对应归宿
					case 53: printf("▲"); break;
					case 4: printf("▽"); break;//箱子三号与对应归宿
					case 54: printf("▼"); break;
					case 88: printf("★"); break;//萌萌的玩家桑 
				}
			}
			printf("\n");
		}
		map[x][y]=former;
		printf("您已经走了%d步。\n",count);//功能完善——步数统计
		printf("如果希望重新开始，请按“Backspace”键；如果希望退出游戏，请按“ESC”键。\n");
		xeon=getch();//接收方向键的第一个字符，同时判断是否有重新开始或者退出游戏的意愿。 
		if(xeon==8){//Backspace键对应的ASCII码为8 
			printf("如果可以重新来过……\n让热爱更澎湃。\n");//正能量语录 
			Sleep(2000);
			system("CLS");
			goto start;//重新来过 
		}else if(xeon==27){//ESC键对应的ASCII码为27 
			printf("欢迎随时再来挑战。\n创造属于你的精彩。\n");//正能量语录 
			Sleep(3000);
			exit(0);
		}
		direction=getch();//方向键需要使用两个字符才能读入。因为在Windows下，方向键由两个字节组成，分别为:'\244'和'\72'up,'\80'down,'\75'left,'\77'right.
		switch(direction){//玩家进行移动 
			case 72: if(map[x-1][y]==52||map[x-1][y]==53||map[x-1][y]==54){//判断玩家上方是否有箱子 
					if(map[x-2][y]==0||map[x-2][y]==2||map[x-2][y]==3||map[x-2][y]==4){//如果有箱子，判断箱子上面是不是墙或者箱子的归宿
						map[x-2][y]=map[x-1][y];//箱子上移
						map[x-1][y]=mapbackup[x-1][y];
						map[x][y]=mapbackup[x][y];
						x-=1;//更改玩家的位置 
						count++;//计数菌，奥利给！ 
					}
				}else{
					if(map[x-1][y]==0||map[x-1][y]==2||map[x-1][y]==3||map[x-1][y]==4){
						x-=1;//玩家上移 
						count++;//计数菌，给力嗷！ 
					}
				}
				break;
			case 80: if(map[x+1][y]==52||map[x+1][y]==53||map[x+1][y]==54){//判断玩家下方是否有箱子 
					if(map[x+2][y]==0||map[x+2][y]==2||map[x+2][y]==3||map[x+2][y]==4){//如果有箱子，判断箱子下面是不是墙或者箱子的归宿 
						map[x+2][y]=map[x+1][y];//箱子下移
						map[x][y]=mapbackup[x][y];
						map[x+1][y]=mapbackup[x+1][y];
						x+=1;//更改玩家的位置 
						count++;//计数菌
					}
				}else{
					if(map[x+1][y]==0||map[x+1][y]==2||map[x+1][y]==3||map[x+1][y]==4){
						x+=1;//玩家下移 
						count++;//计数菌
					}
				}
				break;
			case 77: if(map[x][y+1]==52||map[x][y+1]==53||map[x][y+1]==54){//判断玩家右方是否有箱子 
					if(map[x][y+2]==0||map[x][y+2]==2||map[x][y+2]==3||map[x][y+2]==4){//如果有箱子，判断箱子右面是不是墙 
						map[x][y+2]=map[x][y+1];//箱子右移 
						map[x][y]=mapbackup[x][y];
						map[x][y+1]=mapbackup[x][y+1];
						y+=1;//更改玩家的位置 
						count++;//计数菌
					}
				}else{
					if(map[x][y+1]==0||map[x][y+1]==2||map[x][y+1]==3||map[x][y+1]==4){
						y+=1;//玩家右移 
						count++;//计数菌
					}
				}
				break;
			case 75: if(map[x][y-1]==52||map[x][y-1]==53||map[x][y-1]==54){//判断玩家左方是否有箱子 
					if(map[x][y-2]==0||map[x][y-2]==2||map[x][y-2]==3||map[x][y-2]==4){//如果有箱子，判断箱子左面是不是墙 
						map[x][y-2]=map[x][y-1];//箱子左移 
						map[x][y]=mapbackup[x][y];
						map[x][y-1]=mapbackup[x][y-1];
						y-=1;//更改玩家的位置 
						count++;//计数菌
					}
				}else{
					if(map[x][y-1]==0||map[x][y-1]==2||map[x][y-1]==3||map[x][y-1]==4){
						y-=1;//玩家左移 
						count++;//计数菌 
					}
				}
				break;
		}
		flag=1;
		For(i,1,number){
			if(map[xx[i+1]][yy[i+1]]!=(50+type[i+1])) flag=0;
		}
	}
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;//算出用了多少秒 
	while(duration>=60.0){//如果够一分钟的话，转换成分钟 
		duration-=60.0;
		min++;
	}
	while(min>=60){//如果够一小时的话，转换成小时
		min-=60;
		hour++;
	}
	if(min==0&&hour==0){
		printf("恭喜您成功完成本关卡。\n您一共走了%d步，用时%.2f秒。\n",count,duration);
	}else if(hour==0&&min!=0){
		printf("恭喜您成功完成本关卡。\n您一共走了%d步，用时%d分钟%.2f秒。\n",count,min,duration);
	}else if(hour!=0&&min!=0){
		printf("恭喜您成功完成本关卡。\n您一共走了%d步，用时%d小时%d分钟%.2f秒。\n",count,hour,min,duration);
	}
	grd=fopen("grade.txt","a+");//打开计分板
	if(min==0&&hour==0){
		fprintf(grd,"玩家%s，第%d关的步数为%d，用时%.2f秒。\n",user,choice,count,duration);
	}else if(hour==0&&min!=0){
		fprintf(grd,"玩家%s，第%d关的步数为%d，用时%d分钟%.2f秒。\n",user,choice,count,min,duration);
	}else if(hour!=0&&min!=0){
		fprintf(grd,"玩家%s，第%d关的步数为%d，用时%d小时%d分钟%.2f秒。\n",user,choice,count,hour,min,duration);
	}
	if(fclose(grd)){//关闭计分板，同时设置检查防止出现文件关闭错误的情况。
		printf("关闭文件出现错误。游戏即将退出。\n");
		exit(0);
	}
	printf("您的分数已自动被记录。想继续游玩其他关卡吗？\n请输入Y（是）或N（否）\n");
	scanf("%c",&next);
	if(next=='Y'){
		printf("Hello,未来。");
		Sleep(2000);
		system("CLS");
		goto start;
	}else if(next=='N'){
		printf("感谢游玩，与你心意合一。\nNever Settle.\n");
	}
	system("pause");
	return 0;
}
