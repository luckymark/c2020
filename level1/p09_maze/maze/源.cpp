#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define LINE 20 // 迷宫行数
#define ROW  20 // 迷宫列数
#define OUT_NUM  2 // 出口的值
#define WALL_NUM 1 // 墙的值
#define SPACE_NUM 0 // 空地方的值
#define UP 'w'    // 向上
#define DOWN 's'  // 向下
#define LEFT 'a'  // 向左
#define RIGHT 'd' // 向右
#define ONE_SECOND 1000  //Sleep函数中一秒的值
void printf_maze(const int[][ROW], int, int);
void move_person(char*, int*, int*, const int[][ROW]);
int main()
{
	int maze[LINE][ROW] = {
   //1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//1
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//2
	{1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},//3
	{1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1},//4
	{1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1},//5
	{1,0,1,0,0,0,0,0,1,0,0,1,1,1,1,1,0,0,0,1},//6
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//7
	{1,0,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1},//8
	{1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,1,1,0,1},//9
	{1,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},//10
	{1,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,1,1},//11
	{1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1},//12
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1},//13
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1},//14
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1},//15
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,2},//16
	{1,0,1,1,1,1,1,0,1,0,0,0,0,0,0,1,0,0,1,1},//17
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1},//18
	{1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},//19
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}//20
	};
	char move;
	int hang = 1, lie = 1;//人的位置
	printf_maze(maze,hang,lie);
	while (maze[hang][lie] != OUT_NUM) {
		move_person(&move, &hang, &lie, maze);
		printf_maze(maze, hang, lie);
	}
	printf("\n恭喜您完成游戏\n");
	Sleep(ONE_SECOND);
	return 0;
}
void printf_maze(const int maze[][ROW], int hang, int lie)
{
	system("cls");
	for (int i = 0; i < LINE; i++) {
		for (int j = 0; j < ROW; j++) {
			if (maze[i][j] == WALL_NUM) {
				printf("■");
			}
			else if (i == hang && j == lie)
				printf("**");
			else if (maze[i][j] == SPACE_NUM)
				printf("  ");
			else 
				printf("==");
		}
		printf("\n");
	}
}
void move_person(char* move, int* hang, int* lie,const int maze[][ROW])
{
	scanf_s("%c", move, 1);
	switch (*move)
	{
	case UP:
		if (maze[*hang - 1][*lie] != WALL_NUM)
			*hang -= 1;
		break;
	case DOWN:
		if (maze[*hang + 1][*lie] != WALL_NUM)
			*hang += 1;
		break;
	case LEFT:
		if (maze[*hang][*lie - 1] != WALL_NUM)
			*lie -= 1;
		break;
	case RIGHT:
		if (maze[*hang][*lie + 1] != WALL_NUM)
			*lie += 1;
		break;
	default:break;
	}
}