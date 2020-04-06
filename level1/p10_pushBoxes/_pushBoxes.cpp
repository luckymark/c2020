/*
 地图码表（Nmap.mymap）：N为关卡序数，文件首需要一个数字换行来表示地图大小
  C -- Connected   W -- WALL	N -- NEXT LINE S -- START  B -- BOX  b -- POSITION FOR BOX  F -- FINISH MAP
*/
#include<string.h>
#include<stdio.h> 
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

const int MAXN = 80, WALL = 1, CONNECTED = 0, WANT_POS = 666, SLEEP_TIME = 60, SKIP = 0, DRAW = 1, BOX = 2;
struct Charactor{
	char name;
	int x, y;
}charactor;
int mapLen, _map[MAXN][MAXN], score = 0, want_point = 0, right_point = 0;

void showMessage(char *message);
void showMap(char* filename, int mode);
void drawCharactor();
int move(int x, int y);
static void setPos(int x, int y);
int writeScore(char* map_name, int score);
void gaming(char* map_name);


int main(){	
	memset(_map, CONNECTED, sizeof(_map));
	
	printf("请选择地图，1-2\n");
	char m = getch(); char* map_name;
	while(!(m >= '0'&& m <= '2')){
		m = getch();
	}
	sprintf(map_name, "%cmap.mymap", m);
	
	charactor.name = 'A';	
	showMap(map_name, DRAW);
	
	char msg[] = "请输入一个字符的角色名";
	showMessage(msg);
	m = getch();
	charactor.name = (m >= 'a' && m <= 'z')||(m >= 'A' && m <= 'Z')?m : 'A';
	drawCharactor();	// 重新绘制人物，更改姓名 
	
	char msg2[] = "游戏开始，按 EAC 退出游戏";
	showMessage(msg);
	setPos(charactor.x, charactor.y);
	gaming(map_name);
	
	system("CLS");
	system("PAUSE");
	return 0;
} 


static void setPos(int x, int y){       // Set cursor position
	COORD point = {x, y};
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput, point);
}


void drawCharactor(){
	setPos(charactor.x, charactor.y);
	putchar(charactor.name);
	setPos(charactor.x, charactor.y);
}


bool movBox(int delx, int dely, int x, int y){
	int wantX = delx + x, wantY = dely + y;
	if(_map[wantX][wantY] == WALL)	return false;
	if(_map[wantX][wantY] == WANT_POS){
		_map[wantX][wantY] = WALL;		// prevent charactor form entering it;
		right_point++;
	}
	setPos(x, y);
	putchar(' ');
	_map[x][y] = CONNECTED;
	setPos(wantX, wantY);
	putchar('O');
	if(!(_map[wantX][wantY] == WALL))	_map[wantX][wantY] = BOX;
	setPos(charactor.x, charactor.y);
	return true; 	
}


int move(int delx, int dely){
	
	int x = delx + charactor.x, y = dely + charactor.y;
	if(x < 0 || x > mapLen)	return 0;
	if(y < 0 || y > mapLen)	return 0;
	if(_map[x][y] == WALL)	return WALL;
	if(_map[x][y] == BOX){
		if(movBox(delx, dely, x, y) != 1)
			return BOX;
	}
	//移动光标 并更改人物坐标
	
	drawCharactor();
	if(_map[charactor.x][charactor.y] != WANT_POS)	putchar(' ');
	else putchar('*');
	
	charactor.x = x, charactor.y = y;
	drawCharactor();
	score++;
	
// 下面这一步很想整合一下 
	char m[50];
	sprintf(m, "Your steps: %d", score);
	showMessage(m);
	
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
		 	case 'S': 			// 角色出生坐标要分重绘和不重绘 
		 		if(mode == DRAW){
		 			charactor.x = i, charactor.y = j;		 			 
				 }				
				putchar(' ');
				i++;
				break;
		 	case 'N': putchar('\n'); j++; i=0; break;
		 	case 'b': putchar('*'); _map[i][j] = WANT_POS; want_point++; i++; break;
		 	case 'B': putchar('O'); _map[i][j] = BOX; i++; break;
		 	default: break;
		 }
	}
	fclose(f);
	drawCharactor();
}


void showMessage(char *message){
		
	setPos(0, mapLen+1);
	for(int i = 1; i <= mapLen; i++){
		putchar('-');
	}
	printf("\n                                  ");
	setPos(mapLen, mapLen+1);
	printf("\n%s\n", message);
	for(int i = 1; i <= mapLen; i++){
		putchar('-');
	}
}


void gaming(char* map_name){

    char input;
    while((input = getch()) != 0x1B){
        int result = 0;
        switch(input){
            case -32:				// 这个程序逻辑，如果不用的话，会造成缓存区滞留
                switch(getch()){
                    case 72: result = move(0, -1); break;		// up
                    case 80: result = move(0, +1); break;		// down
                    case 75: result = move(-1, 0); break;		// left
                    case 77: result = move(+1, 0); break;		// right
                    default: break;
                }
                break;
            default: break;
        }
        
        if(input == 'R'){
        	want_point  = 0;
        	showMap(map_name, DRAW);
        	score = 0, right_point = 0;
        	char mes[] = "Your steps：0";
        	showMessage(mes);
		}
		
        if(want_point == right_point){
        	int old_score = writeScore(map_name, score);
			char msg[100];
			sprintf(msg, "Congratulations! Your step number is %d, and the best record is %d", score, old_score); 
            showMessage(msg);
            getch();
            break;
        }
//		Sleep(SLEEP_TIME);    这个程序不需要。。。
    }
}

int writeScore(char* map_name, int score){
	char* file_name = strcat(map_name, "Score");
	FILE* f = fopen(map_name, "r+");
	
	if(f != NULL){
		int old_score;
		fscanf(f, "%d", &old_score);
		if(old_score < score){
			return old_score;
		}
	}
	fclose(f);
	f = fopen(map_name, "w");
	fprintf(f, "%d", score);
	fclose(f);
	return score;
}

