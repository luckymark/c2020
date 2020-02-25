#include <stdio.h>
#include <stdlib.h>

#define L1 1
#define L2 2
#define L3 3
#define L4 4

void printgame(const int*, const int*,const int*, int, int, const char*);
int onemove(int*, int*, int*, char*);
int input_move(char*);


int main()
{
	int A[5] = { 0,L4,L3,L2,L1 };
	int B[5] = { 0 };
	int C[5] = { 0 };
	char move[2] = { 'A','A' };
	int count = 0;
	int why = 0;
	while (B[4] != L1 && C[4] != L1)
	{
		printgame(A, B, C, count, why, move);
		why = input_move(move);
		if(why != 1 && why != 2)
			why = onemove(A, B, C, move);
		if (why == 5 || why == 2)
			count++;
		system("cls");

	}
	why = 0;
	printgame(A, B, C, count, why, move);
	printf("恭喜您，完成汉诺塔游戏！\n");
	printf("您总共移动了%d次！\n", count);
	printf("※提示信息: 输入空格结束窗口");
	while (getchar() != '\n')
		continue;
	return 0;
}

void printgame(const int* A, const int* B, const int* C, int count, int why, const char* move)
{	 
	// 打印游戏标头
	printf("    汉诺塔游戏\n\n");

	// 打印A的堆
	for (int j = 4; j > 0; j--)
		printf("  ");//两个空格
	printf("||\n");
	for (int i = 4; i >= 1; i--) {
		for (int j = 5 - A[i]; j > 0; j--)
			printf("  ");//两个空格
		if (A[i] == 0) {
			printf("\b\b||");
		}
		else {
			for (int j = A[i] * 2 - 1; j > 0; j--)
				printf("■");
		}
		printf("\n");
	}
	for (int j = 0; j < 9; j++)
		printf("==");
	printf("\n");
	for (int j = 0; j < 4; j++)
		printf("  ");
	printf("A:");
	printf("\n\n");

	// 打印B的堆
	for (int j = 4; j > 0; j--)
		printf("  ");//两个空格
	printf("||\n");
	for (int i = 4; i >= 1; i--) {
		for (int j = 5 - B[i]; j > 0; j--)
			printf("  ");//两个空格
		if (B[i] == 0) {
			printf("\b\b||");
		}
		else {
			for (int j = B[i] * 2 - 1; j > 0; j--)
				printf("■");
		}
		printf("\n");
	}
	for (int j = 0; j < 9; j++)
		printf("==");
	printf("\n");
	for (int j = 0; j < 4; j++)
		printf("  ");
	printf("B:");
	printf("\n\n");

	// 打印C的堆
	for (int j = 4; j > 0; j--)
		printf("  ");//两个空格
	printf("||\n");
	for (int i = 4; i >= 1; i--) {
		for (int j = 5 - C[i]; j > 0; j--)
			printf("  ");//两个空格
		if (C[i] == 0) {
			printf("\b\b||");
		}
		else {
			for (int j = C[i] * 2 - 1; j > 0; j--)
				printf("■");
		}
		printf("\n");
	}
	for (int j = 0; j < 9; j++)
		printf("==");
	printf("\n");
	for (int j = 0; j < 4; j++)
		printf("  ");
	printf("C:");
	printf("\n\n");

	// 打印提示信息
	printf(" 您已经移动了%02d次\t", count);
	printf("\n");
	switch (why)
	{
	case 1:
		printf("※提示信息: 您的上次输入不是\"A\"或\"B\"或\"C\" \n");
		break;
	case 2:
		printf("※提示信息: 将%c的块移动到%c上无意义\n", move[0], move[1]);
		break;
	case 3:
		printf("※提示信息: %c上没有块，不可移动\n", move[0]);
		break;
	case 4:
		printf("※提示信息: 大块不能重在小块上面\n");
		break;
	case 5:
		printf("※提示信息: 您已经将%c最上面的块移到了%c上\n", move[0], move[1]);
		break;
	default://why = 0
		break;// 开始游戏或结束游戏
	}

}
int onemove(int* A, int* B, int* C, char* move)
{
	int* p1, * p2;

	//p1
	if (move[0] == 'A')
		p1 = A;
	else if (move[0] == 'B')
		p1 = B;
	else
		p1 = C;
	//p2
	if (move[1] == 'A')
		p2 = A;
	else if (move[1] == 'B')
		p2 = B;
	else
		p2 = C;
	

	int i1 = 4;// 防止指针越界
	while (p1[i1] == 0 && i1 > 0)
		i1--;
	if (i1 == 0) {
		return 3; // 3.※move[0](第一个输入)上没有块，不可移动
	}
	int i2 = 4;// 防止指针越界
	while (p2[i2] == 0 && i2 > 1)
		i2--;
	if (p1[i1] > p2[i2] && p2[i2] != 0) {
		return 4; // 4.※大块不能重在小块上面
	}
	else {
		if (p2[i2] != 0)
			i2++;
		p2[i2] = p1[i1];
		p1[i1] = 0;
		return 5; // 5.※您已经将move[0]的最上面的块移到了move[1]上
	}
}

int input_move(char* move)
{
	printf("请输入您的操作(如：输入AB -> 将A最上面的块移入B) （请大写输入）\n");
	move[0] = getchar();
	move[1] = getchar();
	while (getchar() != '\n')
		continue;
	if (move[0] < 'A' || move[0] > 'C' || move[1] < 'A' || move[1] > 'C') {
		return 1; // 1.※请正确输入
	}
	else if (move[0] == move[1]) {
		return 2; // 2.※无意义的移动
	}
}