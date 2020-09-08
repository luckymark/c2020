//这里是核心算法，但是比较建议取实验报告去看这一部分代码的解释说明
#pragma once
#include <iostream>
#include <time.h>//199行需要
#include <stdlib.h>//200行需要
#include "class.h"

// 寻找最佳位置
seat findbestseat(int color, int c)
{
	if (c == 0)
	{
		//mylength就是MAXxs与MAYys的下标
		mylength = 0;//该点最大分数的可能性个数
	}
	int MAXnumber = -1e9;    //当前局势下，返回分数最大点及该点的分数
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (BOX[i][j].value == -1) {
				//遍历每一个空位置
				int length;        //在该点下了后，可以连成的最大长度
				int emeny;         //当前方向敌子的个数
				int nowi = 0;      //现在遍历到的x坐标
				int nowj = 0;      //现在遍历到的y坐标
				int thescore = 0;  //这个位置的初始分数
				//判断周边有没有棋子，这里的周边是指四个方向一个格子内，然后负一下就是八个方向了
				int is = 0;//相当于一个标记，代表有没有
				for (int k = 0; k < 4; k++)
				{
					nowi = i;
					nowj = j;
					nowi += dx[k];
					nowj += dy[k];
					if (nowi >= 0 && nowj >= 0
						&& nowi <= 18 && nowj <= 18
						&& BOX[nowi][nowj].value != -1)
					{
						is = 1;
						break;
					}//代表了     *
					 //         0 *
					 //         * *  这4个方向，下面就是转180度反过来
					nowi = i;
					nowj = j;
					nowi -= dx[k];
					nowj -= dy[k];
					if (nowi >= 0 && nowj >= 0
						&& nowi <= 18 && nowj <= 18
						&& BOX[nowi][nowj].value != -1)
					{
						is = 1;
						break;
					}
				}
				if (!is)
				{
					//如果周围没有棋子，就不用递归了
					continue;
				}
				//电脑
				BOX[i][j].value = color;//尝试下在这里（其实还没有下，但是先标记上）
				for (int k = 0; k < 4; k++)
				{
					//检测四个方向
					length = 0;
					emeny = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == color)
					{
						length++;
						nowi += dx[k];
						nowj += dy[k];
	
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == !color)//判断之前循环弹出的原因
					{																					//如果在棋盘内但是遇见敌方棋子就加
						                                                                                //或者棋盘外也加
						emeny++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == color)
					{
						length++;
						nowj -= dy[k];
						nowi -= dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == !color)
					{
						emeny++;
					}
					length -= 2;//判断长度（这里是指包括打算下的棋子在内所能连起来的最大长度，然后减掉自己）
					if (length > 4)
					{
						length = 4;
					}
					if (Score[emeny][length] == 1000)
					{
						//己方胜利，结束递归
						BOX[i][j].value = -1;
						return{ i,j,Score[emeny][length] };
					}
					thescore += Score[emeny][length];
					length = 0;
					emeny = 0;
				}
				//敌人（color下子在该处，四个方向得分总和已确定，求！color在这里下是多少得分是多少）
				BOX[i][j].value = !color;
				for (int k = 0; k < 4; k++)
				{
					length = 0;
					emeny = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == !color)
					{
						length++;
						nowj += dy[k];
						nowi += dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == color)
					{
						emeny++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == !color)
					{
						length++;
						nowj -= dy[k];
						nowi -= dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == color)
					{
						emeny++;
					}
					length -= 2;
					if (length > 4)
					{
						length = 4;
					}
					if (Score[emeny][length] == 1000)
					{
						BOX[i][j].value = -1;
						return{ i,j,Score[emeny][length] };
					}
					thescore += Score[emeny][length];
					length = 0;
					emeny = 0;
				}
				//最后，thescore相当于越大，对双方而言，在一步之内都越重要
				BOX[i][j].value = -1;
				//如果已经比最高分数小，就没必要递归了
				if (thescore >= MAXnumber)
				{
					if (c < 3)
					{
						//只能找4层，否则时间太长
						BOX[i][j].value = color;
						//nowscorce代表了4步之内，该点的重要性
						int nowScore = thescore - findbestseat(!color, c + 1).number;//递归求出这个位置的分值
						BOX[i][j].value = -1;
						if (nowScore > MAXnumber)// MAXnumber是指现有局势下，之前遍历了所有子中的nowscore最大值
						{
							//比最高分值大
							MAXnumber = nowScore;
							if (c == 0)//只有第一层要改变下标
							{
								mylength = 0;//下标归0
							}
						}
						if (c == 0)
						{
							//第一层
							if (nowScore >= MAXnumber)
							{
								//把当前位置加入数组
								MAXxs[mylength] = i;
								MAXys[mylength] = j;
								mylength++;//所有等分可能放一起，到时候随机取前mylength长度的可能
							}
						}
					}
					else {
						//如果递归到了最后一层
						if (thescore > MAXnumber)
						{
							//直接更新
							MAXnumber = thescore;
						}
					}
				}
			}
		}
	}
	if (c == 0)
	{
		
		srand(time(NULL));//随机化落子位置，以防止每次都一定走同一个位置，被套路化
		int mynum = rand() % mylength;
		return { MAXxs[mynum],MAXys[mynum],MAXnumber };//把mynum改成0就是套路化的棋子了（相同局势一定走某一个位置）
	}
	//其他层
	return { 0,0,MAXnumber };
}