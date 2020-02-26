#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "func_used.h"

void new_game(void)
{
	/* 以下部分需要文档读取 */
	int num_upboard = 3; // 人加箱子的个数
	int board[LINE][ROW] = {
	{1,1,1,1,1},
	{1,0,2,2,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,1,1,1,1},
	};
	Upthing* upboard = (Upthing*)malloc(sizeof(Upthing) * num_upboard);
	upboard[0].hang = 1;
	upboard[0].lie = 1;
	upboard[1].hang = 2;
	upboard[1].lie = 2;
	upboard[2].hang = 2;
	upboard[2].lie = 3;
	int count_step = 0; // 记录步数
	/* ------------------  */


	print_game(board, upboard, num_upboard);
	while (!isGameover(upboard, num_upboard, board)) 
	{
		if (move_person_box(upboard, num_upboard, board))
			count_step++;
		print_game(board, upboard, num_upboard);
	}
	printf("\n恭喜您用了%d步完成游戏\n", count_step);
	Sleep(ONE_SECOND);
}
bool isGameover(Upthing* upboard, int num_upboard, int board[][ROW])
{
	bool gameover = true;
	for (int i = 1; i < num_upboard; i++) {
		if (board[upboard[i].hang][upboard[i].lie] != BOX_DES) {
			gameover = false;
			break;
		}
	}
	return gameover;
}

void print_game(const int board[][ROW], Upthing* upboard, int num_upboard)
{
	system("cls");
	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < ROW; j++) {
			if (board[i][j] == WALL_NUM) // 是否是墙
				printf("■");
			else if (i == upboard[0].hang && j == upboard[0].lie) // 是否是人
				printf("☆");
			else if (isBOX(upboard, num_upboard, i, j)) // 是否是箱子
				printf("□");
			else if (board[i][j] == SPACE_NUM) // 是否是空地
				printf("  ");
			else if (board[i][j] == BOX_DES)  // 是否是箱子的目的地
				printf("×");
		}
		printf("\n");
	}
}
int isBOX(Upthing* upboard, int num_upboard, int cur_hang, int cur_lie)
{
	int pd = 0;
	for (int k = 1; k < num_upboard; k++) //因为box的ID在upthing里面是从1开始的
	{
		if (upboard[k].hang == cur_hang && upboard[k].lie == cur_lie)
		{
			pd = k;
			break;
		}
	}
	return pd;
}
bool move_person_box(Upthing* upboard,int num_upboard, int maze[][ROW])
{
	char move;
	int ID_box = 0; // 箱子号数（从1开始）
	bool pd = 0;
	scanf_s("%c", &move, 1);
	if (pd = move_or_not(move, upboard, num_upboard, maze, &ID_box)) {
		switch (move)// 移动 人 或者 人和箱子
		{
		case UP:
			upboard[0].hang -= 1;
			if (ID_box)
				upboard[ID_box].hang -= 1;
			break;
		case DOWN:
			upboard[0].hang += 1;
			if (ID_box)
				upboard[ID_box].hang += 1;
			break;
		case LEFT:
			upboard[0].lie -= 1;
			if (ID_box)
				upboard[ID_box].lie -= 1;
			break;
		case RIGHT:
			upboard[0].lie += 1;
			if (ID_box)
				upboard[ID_box].lie += 1;
			break;
		}
	}
	return pd;
}
bool move_or_not(char move, Upthing* upboard,int num_upboard, const int board[][ROW], int* ID_box)
{
	int pd = true;
	switch (move)
	{
	case UP:
		if (board[upboard[0].hang - 1][upboard[0].lie] == WALL_NUM)
			pd = false;
		else if ((*ID_box = isBOX(upboard, num_upboard, upboard[0].hang - 1, upboard[0].lie))) // 赋值并判断是否是箱子
			if (board[upboard[0].hang - 2][upboard[0].lie] == WALL_NUM ||
				isBOX(upboard, num_upboard, upboard[0].hang - 2, upboard[0].lie))
				pd = false;
		break;
	case DOWN:
		if (board[upboard[0].hang + 1][upboard[0].lie] == WALL_NUM)
			pd = false;
		else if ((*ID_box = isBOX(upboard, num_upboard, upboard[0].hang + 1, upboard[0].lie))) // 赋值并判断是否是箱子
			if (board[upboard[0].hang + 2][upboard[0].lie] == WALL_NUM ||
				isBOX(upboard, num_upboard, upboard[0].hang + 2, upboard[0].lie))
				pd = false;
		break;
	case LEFT:
		if (board[upboard[0].hang][upboard[0].lie - 1] == WALL_NUM)
			pd = false;
		else if ((*ID_box = isBOX(upboard, num_upboard, upboard[0].hang, upboard[0].lie - 1))) // 赋值并判断是否是箱子
			if (board[upboard[0].hang][upboard[0].lie - 2] == WALL_NUM ||
				isBOX(upboard, num_upboard, upboard[0].hang, upboard[0].lie - 2))
				pd = false;
		break;
	case RIGHT:
		if (board[upboard[0].hang][upboard[0].lie + 1] == WALL_NUM)
			pd = false;
		else if ((*ID_box = isBOX(upboard, num_upboard, upboard[0].hang, upboard[0].lie + 1))) // 赋值并判断是否是箱子
			if (board[upboard[0].hang][upboard[0].lie + 2] == WALL_NUM ||
				isBOX(upboard, num_upboard, upboard[0].hang, upboard[0].lie + 2))
				pd = false;
		break;
	default:
		pd = false;
		break;
	}
	return pd;
}