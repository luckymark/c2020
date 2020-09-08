#include <iostream>
#include <graphics.h>
#include <conio.h>
#include "other_function.h"
int main()
{
	initgraph(700, 800); // 初始化绘图环境
	setbkcolor(RGB(162, 162, 162));
	cleardevice();
	setbkmode(TRANSPARENT); // 设置透明文字输出背景

	prepare(); // 初始化
	start(); // 游戏开始
}
