#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
const int ROW = 100;
const int COL = 100;
const int NAMELENGTH = 9;
int HEIGHT=0;
int WIDTH=0;
int SCORE = 0;
int LEVEL = 0;
void start();
void move(int x, int y);
void location();
void LoadMap(int level);
void WriteScore(int level);
void PrintMap();
int success();
int map[ROW][COL];
struct Location
{
	int x;
	int y;
};
struct Location ME;
int main() {
start();
LoadMap(LEVEL);
location();
while (1) {
	PrintMap();
	move(ME.x, ME.y);
	system("cls");
	if (success())
	{
		printf("你胜利了\n"
			"得到的分数:%d分", SCORE);
		WriteScore(LEVEL);
		break;
	}
}
}
int success() {
	int success = 1;
	for (int r = 0; r < HEIGHT; r++)
	{
		for (int c = 0; c < WIDTH; c++)
		{
			if (map[r][c] == 3) {
				success = 0;
			}
		}
	}
	return success;
}
void start() {
	int level;
	printf(
		"#######推箱子游戏#######\n"
		"       请选择关卡       \n"
		"         1:第一关       \n"
		"         2:第二关       \n"
	);
	while (1)
	{
		level = _getch();
		if( level == 49 ||
			level == 50 
			)
		{
			LEVEL = level - 48;
			break;
		}
	}
	system("cls");
	
}
void location() {
	for (int r = 0; r < HEIGHT; r++)
	{
		for (int c = 0; c < WIDTH ; c++)
		{
			if (map[r][c] ==2)
			{
				ME.x = c;
				ME.y = r;
				return;
			}
		}
	}
}
void move(int x, int y) {
	char input;
	while (1) {
		input = _getch();
		if (input == 'w' ||
			input == 's' ||
			input == 'a' ||
			input == 'd' ||
			input == 72 ||
			input == 80 ||
			input == 75 ||
			input == 77
			) {
			break;
		}
	}
	switch (input) {
	case 'w':
	case 72:
		if (map[y - 1][x] == 0)
		{
			map[y][x] = 0;
			map[y - 1][x] = 2;
			ME.y = y - 1;
			SCORE++;
		}
		if (map[y - 1][x] == 3)
		{
			if (map[y - 2][x] == 0) {
				map[y][x] = 0;
				map[y - 1][x] = 2;
				map[y - 2][x] = 3;
				ME.y = y - 1;
				SCORE++;
			}
			if (map[y - 2][x] == 4) {
				map[y][x] = 0;
				map[y - 1][x] = 2;
				map[y - 2][x] = 5;
				ME.y = y - 1;
				SCORE++;
			}

		}
		break;

	case 's':
	case 80:
		if (map[y + 1][x] == 0)
		{
			map[y][x] = 0;
			map[y + 1][x] = 2;
			ME.y = y + 1;
			SCORE++;
		};
		if (map[y + 1][x] == 3)
		{
			if (map[y + 2][x] == 0) {
				map[y][x] = 0;
				map[y + 1][x] = 2;
				map[y + 2][x] = 3;
				ME.y = y + 1;
				SCORE++;
			}
			if (map[y + 2][x] == 4) {
				map[y][x] = 0;
				map[y + 1][x] = 2;
				map[y + 2][x] = 5;
				ME.y = y + 1;
				SCORE++;
			};
		}
		break;

	case 'a':
	case 75:
		if (map[y][x - 1] == 0) {
			map[y][x] = 0;
			map[y][x - 1] = 2;
			ME.x = x - 1;
			SCORE++;
		}
		if (map[y][x - 1] == 3)
		{
			if (map[y][x - 2] == 0) {
				map[y][x] = 0;
				map[y][x - 1] = 2;
				map[y][x - 2] = 3;
				ME.x = x - 1;
				SCORE++;
			}
			if (map[y][x - 2] == 4) {
				map[y][x] = 0;
				map[y][x - 1] = 2;
				map[y][x - 2] = 5;
				ME.x = x - 1;
				SCORE++;
			};
		}
		break;

	case 'd':
	case 77:
		if (map[y][x + 1] == 0)
		{
			map[y][x] = 0;
			map[y][x + 1] = 2;
			ME.x = x + 1;
			SCORE++;
		};
		if (map[y][x + 1] == 3)
		{
			if (map[y][x + 2] == 0) {
				map[y][x] = 0;
				map[y][x + 1] = 2;
				map[y][x + 2] = 3;
				ME.x = x + 1;
				SCORE++;
			}
			if (map[y][x + 2] == 4) {
				map[y][x] = 0;
				map[y][x + 1] = 2;
				map[y][x + 2] = 5;
				ME.x = x + 1;
				SCORE++;
			}
		};
		break;


	}
}
void LoadMap(int level){
	char levelChose[NAMELENGTH];
	sprintf(levelChose, "map%d.txt", level);
	FILE* fp = fopen(levelChose, "r");
	fscanf(fp, "%d %d", &HEIGHT, &WIDTH);
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH;j++) {
			fscanf(fp, "%d", &map[i][j]);
		}
	}
	fclose(fp);
}
void PrintMap() {
	for (int r = 0; r < HEIGHT; r++)
	{
		for (int c = 0; c < WIDTH; c++)
		{
			switch (map[r][c])
			{
			case 0:putchar(' '); break;
			case 1:putchar('#'); break;
			case 2:putchar('O'); break;
			case 3:putchar('B'); break;
			case 4:putchar('@'); break;
			case 5:putchar('!'); break;
			default:
				break;
			}
		}
		printf("\n");
	}
	printf("分数：%d\n", SCORE);
	printf("'O':玩家,'B':箱子,'@':目标点");
}
void WriteScore(int level) {
	char levelChose[NAMELENGTH];
	errno_t eResult;
	FILE* fp = NULL;
	sprintf(levelChose, "map%d.txt", level);
	eResult = fopen_s(&fp, levelChose, "a+");
	fprintf(fp, "分数：%d",SCORE);
	fclose(fp);
}

