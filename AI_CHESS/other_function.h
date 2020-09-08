//一些除了核心算法的函数都放在这里
#pragma once
#include <iostream>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include "class.h"
#include "ai_function.h"

void draw()
{
	int number = 0;
	// 要加上的坐标数字
	TCHAR strnum[19][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") ,_T("14"),_T("15") ,_T("16") ,_T("17"),_T("18"),_T("19") };
	LOGFONT style;
	gettextstyle(&style);
	settextstyle(0, 0, NULL);
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			BOX[i][j].draw(); // 把每一小块画出来
			if (BOX[i][j].isnew == true)
			{
				BOX[i][j].isnew = false; // 把之前下棋位置的黑框清除
			}
		}
	}
	// 画坐标
	for (int i = 0; i < 19; i++)
	{
		outtextxy(75 + number, 35, strnum[i]);
		outtextxy(47, 55 + number, strnum[i]);
		number += 30;
	}
	settextstyle(&style);
}

// 负责给每一个BOX赋值xy的坐标与对应的棋盘样式
void prepare()
{
	win = -1;// 如果你想欺负电脑，请修改这里（dog）
	for (int i = 0, k = 0; i < 570; i += 30)
	{
		for (int j = 0, g = 0; j < 570; j += 30)
		{
			int modle = 0;  // 每一小块的种类
			BOX[k][g].value = -1;
			BOX[k][g].color = RGB(204, 177, 136);// 棋盘底色，贴心的棕色
			BOX[k][g].x = 65 + j;
			BOX[k][g].y = 50 + i;//这个数据还要和一开始构建的窗口大小贴合，后面的文字图片显示都要看这个，麻烦
			if (k == 0 && g == 0)//每一个model的种类在class.h中的box::draw()中标注了
			{
				modle = 8;
			}
			else if (k == 0 && g == 18)
			{
				modle = 7;
			}
			else if (k == 18 && g == 18)
			{
				modle = 6;
			}
			else if (k == 18 && g == 0)
			{
				modle = 5;
			}
			else if (k == 0)
			{
				modle = 3;
			}
			else if (k == 18)
			{
				modle = 4;
			}
			else if (g == 0)
			{
				modle = 1;
			}
			else if (g == 18)
			{
				modle = 2;
			}
			else  if ((k == 3 && g == 3) || (k == 3 && g == 15) || (k == 15 && g == 3) || (k == 15 && g == 15) || (k == 3 && g == 9) || (k == 9 && g == 3) || (k == 15 && g == 9) || (k == 9 && g == 15) || (k == 9 && g == 9))
			{
				modle = 9;
			}
			else
			{
				modle = 0;
			}
			BOX[k][g].modle = modle;
			g++;
		}
		k++;
	}
}

// 判断游戏是否结束了
void isWIN()
{
	bool isfull = true; // 棋盘是否满了
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (BOX[i][j].value != -1)
			{
				// 遍历每个可能的位置
				int nowcolor = BOX[i][j].value; // 现在遍历到的颜色
				int length[4] = { 0,0,0,0 };    // 四个方向的长度
				for (int k = 0; k < 4; k++)
				{
					// 原理同寻找最佳位置
					int nowi = i;
					int nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == nowcolor)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == 1 - nowcolor)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
				}
				for (int k = 0; k < 4; k++)
				{
					if (length[k] >= 5) {
						// 如果满五子
						if (nowcolor == playercolor)
						{
							win = playercolor; // 玩家胜
						}
						if (nowcolor == 1 - playercolor)
						{
							win = 1 - playercolor; // 电脑胜
						}
					}
				}
			}
			else
			{
				//如果为空
				isfull = false;//棋盘没满
			}
		}
	}
	if (isfull)
	{
		// 如果棋盘满了
		win = 2; // 平局
	}
}
//主体函数（就是它架空了main函数）
void start()
{
	bool isinit;
	
	int oldi = 0;
	int oldj = 0;// 上一个鼠标停的坐标
	
	setfillcolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	fillcircle(150, 720, 20);
	setfillcolor(WHITE);
	fillcircle(550, 720, 20);//画两个棋子以供选择玩家颜色
	
	setfillcolor(RGB(204, 177, 136));// 绘制背景
	solidrectangle(40, 25, 645, 630);//画一个矩形
	settextstyle(30, 15, 0, 0, 0, 1000, false, false, false);// 设置字体样式
	settextcolor(BLACK);
	
	outtextxy(200, 650, _T("按棋子选择你的颜色"));// 提醒玩家选择颜色

	box choose[2];//这里再划取两个小块来判断玩家的选择
	choose[0].x = 130;
	choose[1].x = 530;

	while (playercolor < 0)//每选出来就一直循环
	{
		MOUSEMSG mouse = GetMouseMsg();//得到鼠标信息，是一个类
		for (int i = 0; i < 2; i++)
		{
			if (mouse.x > choose[i].x && mouse.x < choose[i].x + 40 && mouse.y>700 && mouse.y < 740)
			{
				if (mouse.mkLButton)//如果点击了左键
				{
					if (i == 0) playercolor = 1;
					if (i == 1) playercolor = 0;//判断在哪里点击的
				}
			}
		}
	}
	
	setfillcolor(RGB(162, 162, 162));
	solidrectangle(130, 700, 170, 740);
	solidrectangle(530, 700, 570, 740);//画两个矩形把之前的圆覆盖掉

	settextcolor(RGB(162, 162, 162));
	outtextxy(200, 650, _T("按棋子选择你的颜色"));

	settextcolor(BLACK);
	// 告知玩家的颜色选择是什么并在下面画出来
	if (playercolor == 0)
	{
		isinit = 1;
		outtextxy(290, 650, _T("你为白棋"));
		whoplay = 1;
		setfillcolor(WHITE);
		setlinestyle(PS_SOLID, 1);
		fillcircle(350, 720, 20);

	}
	else
	{
		isinit = 0;
		outtextxy(290, 650, _T("你为黑棋"));
		whoplay = 0;
		setfillcolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		fillcircle(350, 720, 20);
	}
	draw(); // 绘制
	while (1)
	{
	NEXTPLAYER:
		if (whoplay == 0)//玩家黑
		{
			// 玩家下棋（这个判断点击下棋的一段代码学过来发现很神奇）
			MOUSEMSG mouse = GetMouseMsg(); // 得到鼠标的信息
			for (int i = 0; i < 19; i++)
			{
				for (int j = 0; j < 19; j++)
				{
					if (mouse.x > BOX[i][j].x && mouse.x<BOX[i][j].x + 30//判断x坐标
						&& mouse.y>BOX[i][j].y && mouse.y < BOX[i][j].y + 30//判断y坐标
						&& BOX[i][j].value == -1)//判断是否是空位置
					{
						if (mouse.mkLButton)
						{
							// 如果按下了左键
							BOX[i][j].value = playercolor; // 下棋
							BOX[i][j].isnew = true;        // 新位置更新
							oldi = -1;
							oldj = -1;
							// 下一个玩家
							whoplay = 1;
							goto DRAW;
						}
						
						BOX[oldi][oldj].isnew = false;
						BOX[oldi][oldj].draw();
						BOX[i][j].isnew = true;
						BOX[i][j].draw();
						oldi = i;
						oldj = j;// 更新选择框
					}
				}
			}
		}
		else
		{
			// 电脑下棋
			if (isinit)
			{
				// 开局情况
				isinit = 0;
				int drawi = 9;
				int drawj = 9;
				while (BOX[drawi][drawj].value != -1)
				{
					drawi--;
					drawj++;
				}
				BOX[drawi][drawj].value = 1 - playercolor;
				BOX[drawi][drawj].isnew = true;
			}
			else
			{
				seat best;
				best = findbestseat(1 - playercolor, 0); // 寻找最佳位置
				BOX[best.i][best.j].value = 1 - playercolor;//下在最佳位置
				BOX[best.i][best.j].isnew = true;
			}
			whoplay = 0;//轮到玩家下了
			goto DRAW; // 更新一下图
		}
	}
DRAW: // 绘制
	isWIN(); // 检测输赢
	draw();
	oldi = 0;
	oldj = 0;
	if (win == -1)
	{
		// 如果没有人胜利并且没有下满
		Sleep(500);
		goto NEXTPLAYER; // 前往下一个玩家
	}
	// 游戏结束
	settextcolor(RED);
	Sleep(1000);
	settextstyle(100, 0, NULL);
	if (win == 0)
	{
		outtextxy(200, 250, _T("白方胜！"));
	}
	if (win == 1)
	{
		outtextxy(200, 250, _T("黑方胜！"));
	}
	if (win == 2)
	{
		outtextxy(200, 250, _T("平局！"));
	}
	// 给点时间缓缓
	Sleep(5000);
	return;
}