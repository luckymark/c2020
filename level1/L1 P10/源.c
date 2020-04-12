#include<stdio.h>
#define Length 7
#pragma warning(disable : 4996)
void PrintMap(int map[Length][Length]);
void OpenFile(int map[Length][Length], char* fd, struct point* pp);
int Player(int map[Length][Length], struct point* pp);
void Save(char* fd);
int map1[Length][Length];
int map2[Length][Length];

struct point {
	int x, y;
};
struct point p1;
struct point p2;
struct point* pp1 = &p1;
struct point* pp2 = &p2;
int box = 2;
int step = 0;
int main(void)  //输入wasd加回车
{
	OpenFile(map1, "D:\\map1.txt",pp1);
	OpenFile(map2, "D:\\map2.txt",pp2);
	if (Player(map1, pp1)) {
			Save("D:\\map1.txt");
		step = 0;
		Player(map2, pp2);
		Save("D:\\map2.txt");
	}
	return 0;
}
void PrintMap(int map[Length][Length])
{
	for (int i = 0; i < Length; i++) {
		for (int j = 0; j < Length; j++) {

			switch (map[i][j]) {
			case 0:printf("▉"); break;
			case 1:printf("  "); break;
			case 2:printf("人"); break;
			case 3:printf("口"); break;
			case 4:printf("囚"); break;
			case 5:printf("箱"); break;
			case 6:printf("中"); break;//D:\map1.txt
			}
		}
		printf("\n");
	}
}

void Save(char* fd)
{
	FILE* f;
	f = fopen(fd, "a+");
	fprintf(f, " %d", step);
	fclose(f);
}
void OpenFile(int map[Length][Length], char* fd, struct point* pp)
{
	FILE* f;
	if ((f = fopen(fd, "r")) == NULL){
		printf("未打开\n");
		exit(0);
	}else{
		for (int i = 0; i < Length; i++)
			for (int j = 0; j < Length; j++){
				fscanf(f, "%d", &map[i][j]);
				if (map[i][j] == 2){
					pp->x = i;
					pp->y = j;
				}
				/*else if (map[i][j] == 3)
					box++;*/
			}
	}
	fclose(f);
}
int Player(int map[Length][Length], struct point* pp)
{
	PrintMap(map);
	int direction;
	int now_ok = 0;
	do {
		char c,en;
		c = getchar();			//getchar，scanf不接受回车，用另一个getchar吸收掉
		en = getchar();
		step++;
		int direction = c;
		switch (direction) {
		case 97://a
			if (map[pp->x][pp->y - 1] == 1 || map[pp->x][pp->y - 1] == 3) {
				map[pp->x][pp->y - 1] += 1;
				map[pp->x][pp->y] -= 1;
				pp->y -= 1;
			}
			else if (map[pp->x][pp->y - 1] == 5 && (map[pp->x][pp->y - 2] == 1 || map[pp->x][pp->y - 2] == 3))
			{
				if (map[pp->x][pp->y - 2] == 3) { 
					map[pp->x][pp->y - 2] = 6;
					now_ok++;
				}else map[pp->x][pp->y - 2] = 5;
				map[pp->x][pp->y] = 1;
				map[pp->x][pp->y - 1] = 2;
				pp->y -= 1;
			}
			break;
		case 100://d
			if (map[pp->x][pp->y+1] == 1 || map[pp->x][pp->y+1] == 3) {
				map[pp->x][pp->y+1] += 1;
				map[pp->x][pp->y] -= 1;
				pp->y += 1;
			}
			else if (map[pp->x][pp->y+1] == 5 && (map[pp->x][pp->y+2] == 1 || map[pp->x][pp->y + 2] == 3))
			{
				if (map[pp->x][pp->y + 2] == 3)
				{
					map[pp->x][pp->y + 2] = 6;
					now_ok++;
				}
				else map[pp->x][pp->y + 2] = 5;
				map[pp->x][pp->y] = 1;
				map[pp->x][pp->y+1] = 2;
				pp->y += 1;
			}
			break;
		case 119://w
			if (map[pp->x - 1][pp->y] == 1 || map[pp->x - 1][pp->y] == 3) {
				map[pp->x - 1][pp->y] += 1;
				map[pp->x][pp->y] -= 1;
				pp->x -= 1;
			}
			else if (map[pp->x - 1][pp->y] == 5 && (map[pp->x - 2][pp->y] == 1 || map[pp->x - 2][pp->y] == 3))
			{
				if (map[pp->x - 2][pp->y] == 3) {
					map[pp->x - 2][pp->y] = 6;
					now_ok++;
				}
				else map[pp->x-2][pp->y] = 5;
				map[pp->x][pp->y] = 1;
				map[pp->x - 1][pp->y] = 2;
				pp->x -= 1;
			}
			break;
		case 115://s
			if (map[pp->x + 1][pp->y] == 1 || map[pp->x + 1][pp->y] == 3) {
				map[pp->x + 1][pp->y] += 1;
				map[pp->x][pp->y] -= 1;
				pp->x += 1;
			}
			else if (map[pp->x + 1][pp->y] == 5 && (map[pp->x + 2][pp->y] == 1 || map[pp->x + 2][pp->y] == 3))
			{
				if (map[pp->x + 2][pp->y] == 3) {
					map[pp->x + 2][pp->y] = 6;
					now_ok++;
				}
				else map[pp->x + 2][pp->y] = 5;
				map[pp->x][pp->y] = 1;
				map[pp->x + 1][pp->y] = 2;
				pp->x += 1;
			}
			break;
		}
		system("cls");
		PrintMap(map);
	} while (now_ok != box);
	return 1;
}