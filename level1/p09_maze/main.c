#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // sorry for mac users and linux users

#define SHAPE_X 25
#define SHAPE_Y 25
#define BEGIN_X 0
#define BEGIN_Y 1
#define END_X 24
#define END_Y 23
#define MARGIN 1
#define bool int
#define false 0
#define true 1

const char dirs[2][10] = {"map.bin", "win.bin"};
const char dchar[3][3] = {"  ", "▓", "●"};
bool map[SHAPE_X][SHAPE_Y];

void print(short x, short y, int n);
void loadScene(const char dir[]);

int main() {
	char cmd[100];
	CONSOLE_CURSOR_INFO cci = {1, false};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	sprintf(cmd, "mode con lines=%d cols=%d", SHAPE_X + MARGIN *2, SHAPE_Y * 2 + MARGIN * 4);
	system("title maze");
	system(cmd);

	loadScene(dirs[0]);
	map[BEGIN_X][BEGIN_Y] = map[END_X][END_Y] = false;
	int x = BEGIN_X, y = BEGIN_Y, dx = 0, dy = 0;
	print(x, y, 2);

	while(!(x == END_X && y == END_Y)) {
		if (kbhit()) {
			bool move = true;
			switch (getch()) {
				case 72: dx = -1; dy = 0; break; // ↑
				case 80: dx = +1; dy = 0; break; // ↓
				case 75: dy = -1; dx = 0; break; // ←
				case 77: dy = +1; dx = 0; break; // →
				default: move = false;
			}
			int tx = x + dx, ty = y + dy;
			if (move && tx >= 0 && ty >= 0 && tx < 25 && ty < 25 && !map[tx][ty]) {
				print(x, y, 0);
				print(x = tx, y = ty, 2);
			}
		}
	}

	system("cls");
	loadScene(dirs[1]);
	print(16, 4, 0);
	system("pause");
	return 0;
}

void print(short x, short y, int n) {
	COORD pos = {y = y * 2 + 2, x = x + 1};
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, pos);
	printf("%s", dchar[n]);
}

void loadScene(const char dir[]) {
	unsigned char t;
	int i = 0, j = 0;
	FILE *fp = fopen(dir, "rb");
	for (int loop = SHAPE_X * SHAPE_Y / 8; loop; loop--) {
		fread(&t, 1, 1, fp);
		for (int k = 7; k >= 0; k--) {
			int x = i, y = j + k;
			if (y >= SHAPE_Y) {
				y -= SHAPE_Y;
				x++;
			}
			map[x][y] = t & 1;
			t >>= 1;
		}
		if ((j += 8) >= SHAPE_Y) {
			j -= SHAPE_Y;
			i++;
		}
	}
	// when SHAPE_X * SHAPE_Y % 8 == 1
	fread(&t, 1, 1, fp);
	map[SHAPE_X - 1][SHAPE_Y - 1] = ((t >> 7) & 1);
	fclose(fp);
	for (i = 0; i < SHAPE_X; i++) {
		for (j = 0; j < SHAPE_Y; j++) {
			if (map[i][j]) {
				print(i, j, 1);
			}
		}
	}
}
