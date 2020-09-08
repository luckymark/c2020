//存放类与类函数与全局变量
#pragma once
#include <iostream>
#include <graphics.h>
#include <conio.h>

class seat //只在ai_function中起作用
{
public:
	int i = 0;      // x 坐标
	int j = 0;      // y 坐标
	int number = 0; // 分数
};

class box //每一块储存棋子的种类，棋子的坐标，
{
public:
	void draw();            //画该块的图像
public:
	int x = 0;              
	int y = 0;              
	int value = -1;         // 代表这个点下了什么棋（黑棋：1，白棋：0，空位：-1）
	int modle = 0;          // 对361个块分类（只是判断这个点在棋盘上的位置，以便画不同的线条）
	bool isnew = false;     // 是否有选择框（鼠标悬停时有指示框，画图时需要更新）
	COLORREF color = WHITE; // 棋盘背景色
};

// 全局变量
box BOX[19][19];      // 把棋盘划分成19*19块
int win = -1;         // 谁赢了（0代表白棋，1代表黑棋，2代表平局）
int whoplay = 0;      // 轮到谁下棋了（1代表电脑下，0代表玩家下）
int playercolor = -1;  // 玩家颜色（0为白色，1为黑色）
int dx[4]{ 1,0,1,1 }; // 代表了- | \ / 四个方向，到时候直接调用
int dy[4]{ 0,1,1,-1 };
int Score[3][5] = //评分表（所实话在网上找到的这个方法算是比较简单的了，难的不会了...）
{
	{ 0, 80, 250, 1000, 1000 }, // 敌方子（包括墙）个数为0，然后是按照我方在某个点下了后的最大连续个数-1来排序0~4
	{ 0, 0,  80,  250, 1000 }, // 敌方子（包括墙）个数为1
	{ 0, 0,  0,   80,  1000 }  // 敌方子（包括墙）个数为2
};
int MAXxs[361];   //每种最高分可能性的x坐标
int MAXys[361];   //每种最高分可能性的y坐标
int mylength = 0; //该点最大分数的可能性个数

void box::draw()
{
	COLORREF thefillcolor = getfillcolor(); // 备份填充颜色
	setlinestyle(PS_SOLID, 2);              // 线样式设置
	setfillcolor(color);                    // 填充颜色设置
	solidrectangle(x, y, x + 30, y + 30);   // 绘制无边框的正方形
	if (isnew)
	{
		// 如果是最新下的棋子，那么就画框
		setlinecolor(LIGHTGRAY);
		line(x + 1, y + 2, x + 8, y + 2);
		line(x + 2, y + 1, x + 2, y + 8);
		line(x + 29, y + 2, x + 22, y + 2);
		line(x + 29, y + 1, x + 29, y + 8);
		line(x + 2, y + 29, x + 8, y + 29);
		line(x + 2, y + 22, x + 2, y + 29);
		line(x + 29, y + 29, x + 22, y + 29);
		line(x + 29, y + 22, x + 29, y + 29);
	}
	setlinecolor(BLACK);
	switch (modle)
	{
		// 根据每一小块的不同位置来画图
	case 0:
		line(x + 15, y, x + 15, y + 30);
		line(x - 1, y + 15, x + 30, y + 15);
		break;
		// 一般点
	case 1:
		line(x + 14, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// 左边边缘点
	case 2:
		line(x - 1, y + 15, x + 15, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// 右边边缘点
	case 3:
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		// 上边边缘点
	case 4:
		line(x + 15, y, x + 15, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		// 下边边缘点
	case 5:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 15);
		line(x + 15, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		// 左下角
	case 6:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 15);
		line(x - 1, y + 15, x + 15, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		// 右下角
	case 7:
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 15, y + 15);
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// 右上角
	case 8:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y + 15, x + 30, y + 15);
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// 左上角
	case 9:
		line(x + 15, y, x + 15, y + 30);
		line(x - 1, y + 15, x + 30, y + 15);
		setfillcolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 5);
		break;
		// 特殊的九个点（还要画一个小圆）
	}
	switch (value)
	{
	case 0: // 白棋
		setfillcolor(WHITE);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 13);
		break;
	case 1: // 黑棋
		setfillcolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 13);
		break;
	}
	setfillcolor(thefillcolor); // 还原填充色
}