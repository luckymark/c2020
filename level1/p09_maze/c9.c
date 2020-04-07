#include<stdio.h>
#include <stack>
#include<conio.h>

#define ROW 6
#define COL 6

void PrintMap();
int Success(int x,int y);
void move(int x, int y,char input);
void Location();
void Exit();
char inputchar();
int X;
int Y;
int XEnd;
int YEnd;


int main()
{
	Location();
	Exit();
	char input;
	while (1)
	{
		PrintMap();
		input = inputchar();
		move(X,Y,input);
		if (Success(X, Y)) {
			break;
		}
		system("cls");
	}

}

char map[ROW][COL] = {

		{'#', '#', '#', '#', '#', '#'},

		{'#', 'O', '#', '#', ' ', ' '},

		{'#', ' ', '#', '#', ' ', '#'},

		{'#', ' ', ' ', '#', ' ', '#'},

		{'#', '#', ' ', ' ', ' ', '#'},

		{'#', '#', '#', '#', '#', '#'}

};//µØÍ¼

void Exit() {
	for (int r = 1; r < ROW - 1; r++)
	{
		if (map[r][0]==' '&& map[r-1][0] == '#' && map[r+1][0] == '#')
		{
			XEnd = 0;
			YEnd = r;
			break;
		}
		if (map[r][ROW - 1] == ' ' && map[r - 1][ROW - 1] == '#' && map[r + 1][ROW - 1] == '#')
		{
			XEnd = ROW - 1;
			YEnd = r;
			break;
		}
	}
	for (int c = 1; c < COL - 1; c++) {
		if (map[0][c] == ' ' && map[0][c - 1] == '#' && map[0][c + 1] == '#') {
			XEnd =c ;
			YEnd =0 ;
			break;
		}
		if (map[COL - 1][c] == ' ' && map[COL - 1][c - 1] == '#' && map[COL - 1][c + 1] == '#') {
			XEnd = c;
			YEnd = COL - 1;
			break;
		}

	}
};

void PrintMap() {
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			printf("%c",map[r][c]);
		}
		printf("\n");
	}
};

int Success(int x,int y) {
	if (x==XEnd&&y==YEnd)
	{
		system("cls");
		printf("»ñÊ¤");
		return 1;
	}
	return 0;
}

char inputchar() {
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
	return input;
};

void move(int x, int y,char input) {
	switch (input) {
	case 'w':
	case 72: if (map[y - 1][x] == ' ')
	{
		char temp = map[y - 1][x];
		map[y - 1][x] = map[y][x];
		map[y][x] = temp;
		Y = y - 1;
	}break;

	case 's':
	case 80:if (map[y + 1][x] == ' ')
	{
		char temp = map[y + 1][x];
		map[y + 1][x] = map[y][x];
		map[y][x] = temp;
		Y = y + 1;
	}break;

	case 'a':
	case 75:if (map[y][x - 1] == ' ') {
		char temp = map[y][x - 1];
		map[y][x - 1] = map[y][x];
		map[y][x] = temp;
		X = x - 1;
	}break;
		
	case 'd':
	case 77:if (map[y][x + 1] == ' ') {
		char temp = map[y][x + 1];
		map[y][x + 1] = map[y][x];
		map[y][x] = temp;
		X = x + 1;
	}break;
	}
}

void Location() {
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			if (map[r][c] == 'O')
			{
				X = c;
				Y = r;
				return;
			}
		}
	}
}

