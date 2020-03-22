// 迷宫文件保存读取，方向键控制（ch控制），动画，windows平台
// 地图码表（xx.mymap）：文件首需要一个数字换行来表示地图大小 C -- Connected   W -- WALL	  N -- 换行    S -- START  E -- END	   F -- Finsh map
#include<cstring>
#include<stdio.h> 
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

const int maxn = 80, WALL = 1, CONNECTED = 0, EXIT = 666, SLEEP_TIME = 60, SKIP = 0, DRAW = 1;
struct _charactor{
	char name = 'A';
	int x, y;
}charactor;
int mapLen, _map[maxn][maxn], ChangeCPos = 1;

static void setPos(int x, int y){
	COORD point = {x, y};
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point);
}


int move(int x, int y){
	if(x < 0 || x > mapLen)	return 0;
	if(y < 0 || y > mapLen)	return 0;
	if(_map[x][y] == WALL)	return WALL;
	//移动光标 并更改人物坐标 
	
	charactor.x = x, charactor.y = y;
	putchar(' ');
	setPos(x,y);
	putchar(charactor.name);
	setPos(x,y);
	
	if(_map[x][y] == EXIT)	return EXIT;

	return CONNECTED;
}


void showMap(char* filename, int mode){
	system("cls");
	setPos(0,0);
	FILE* f = fopen(filename, "r");		//菜，就用 fgetc 读了
	fscanf(f, "%d", &mapLen);
	int ch, i = 0, j = 0;
	while((ch=fgetc(f)) != 'F'){		//终止
		 switch(ch){
		 	case 'W': putchar('#'); _map[i][j] = WALL; i++; break;
		 	case 'C': putchar(' '); i++; break;
		 	case 'S': 			// 角色出生坐标要重绘，呕 
		 		if(ChangeCPos && mode == DRAW){
		 			putchar(charactor.name);
		 			charactor.x = i, charactor.y = j;
		 			ChangeCPos = 0;
		 			i++; 
		 			break;
				 }
				else{
					putchar(' ');
					i++;
					break;
				}
		 	case 'N': putchar('\n'); j++; i=0; break;
		 	case 'E': putchar(' '); _map[i][j] = EXIT; i++; break;
		 	default: break;
		 }
	}
	fclose(f);
}


void showMessage(char *message, int mode){
	showMap("map1.mymap", mode);		//这个函数里有清屏 
	setPos(0, mapLen+1);
	for(int i = 1; i <= mapLen; i++){
		putchar('-');
	}
	printf("\n%s\n", message);
	for(int i = 1; i <= mapLen; i++){
		putchar('-');
	}
}


int main(){	
	memset(_map, CONNECTED, sizeof(_map));
	showMessage("请输入一个字符的角色名", SKIP);
	charactor.name = getch();
	showMessage("游戏开始，按 EAC 退出游戏", DRAW);
	setPos(charactor.x, charactor.y);
	
	char input;
	while((input = getch()) != 0x1B){
		int result = 0;
		switch(input){
			case -32:				// 这个程序逻辑，如果不用的话，会造成缓存区滞留 
				switch(getch()){
					case 72: result = move(charactor.x, charactor.y-1); break;		// up 
					case 80: result = move(charactor.x, charactor.y+1); break;		// down
					case 75: result = move(charactor.x-1, charactor.y); break;		// left
					case 77: result = move(charactor.x+1, charactor.y); break;		// right
					default: break;
				}
				break;	
			default: break;	
		}
		if(result == EXIT){
			showMessage("Congratulations!!!", DRAW);
			getch(); 
			break; 
		}
//		Sleep(SLEEP_TIME);    这个程序不需要。。。 
	}
	system("CLS");
	system("PAUSE");
	return 0;
} 
