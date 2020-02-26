#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

const int Len = 30;
const int Height = 10;/*地图的长宽 包括边界*/
const int cor_x = 6;
const int cor_y = 6;/*在console输出的原点*/
const int Enter_x = 1;/*入口坐标*/
const int Enter_y = 2;
const int Exit_x = 10;/*出口坐标*/
const int Exit_y = 29;
const int max = 64;/*控制障碍物生成概率的分母和分子*/
const int lim = 49;
int dir[4][2]={{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool judge_map(int (&pr)[50][50], bool (&vis)[50][50], int x, int y)/*判断地图是否有解*/
{
	if(x == Exit_x && y == Exit_y) return true;
	if(x < 1 || x > Height || y < 1 || y > Len|| vis[x][y] || (pr[x][y] != 0) ) return false;
	
	vis[x][y] = true;
	
	int i;
	bool flag = false;
	
	for(i = 0;i < 4;i++)
	{
		if(judge_map(pr, vis, x + dir[i][0], y + dir[i][1]))
		flag = true;
	}
	return flag;
}
void pf_map(int (&pr)[50][50], HANDLE hOut)/*打印地图*/
{
	int i,j;/*注地图中的数值 0 空地 1 障碍 2 竖着的墙 3 横着的墙 4 拐角的墙*/
	DWORD a;
	for(i = 1;i <= Height;i++)
	for(j = 1;j <= Len;j++)
	{
		COORD pos = {cor_y + j, cor_x + i};
		char *s;
		if(i == Enter_x && j == Enter_y) s = "*";
		else if(pr[i][j] == 0) s = " ";
		else if(pr[i][j] == 1) s = "X";
		else if(pr[i][j] == 2) s = "|";
		else if(pr[i][j] == 3) s = "-";
		else if(pr[i][j] == 4) s = "+";
		WriteConsoleOutputCharacter(hOut, s, 1, pos, &a);
	}
}
int main()
{
	srand(time(0));
	FILE *fin;
	HANDLE handle_out;
	CONSOLE_CURSOR_INFO CursorInfo;
	COORD posText;
	COORD posEnter;
	COORD posExit;
	COORD pos_now;/*控制当前点与将要走到的目标点*/
	COORD pos_pre;
	DWORD a;
	int i,j;
	int pr[50][50];/*地图*/
	bool vis[50][50];
	
	handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	
	GetConsoleCursorInfo(handle_out, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle_out, &CursorInfo);
	
	
	posText.X = cor_y;
	posText.Y = cor_x;
	
 	posEnter.X = Enter_y + cor_y;
	posEnter.Y = Enter_x + cor_x;
	
	posExit.X = Exit_y + cor_y;
	posExit.Y = Exit_x + cor_x;
 	
 	pos_now = posEnter;
 	

	/*0 space 1 barrier 2 wall_straight 3 wall_across 4 wall_corner 5 peo*/
	bool flag;
	do
	{
		for(i = 1;i <= Height;i++)
		{
			for(j = 1;j <= Len;j++)
			{
				int judge_j = (j == 1 || j == Len) , judge_i = (i == 1 || i == Height);
				if(judge_i && judge_j) pr[i][j] = 4;
				else if(judge_i) pr[i][j] = 3;
				else if(judge_j) pr[i][j] = 2;
				else
				{
					int rd = rand() % max;
					if(rd >= lim)
					pr[i][j] = 1;
					else 
					pr[i][j] = 0;
				}   
			}
		}
		for(i = 1;i <= Height;i++)
		for(j = 1;j <= Len;j++)
		vis[i][j] = false;
		pr[Enter_x][Enter_y] = 0;
		pr[Exit_x][Exit_y] = 0;
		flag = judge_map(pr, vis, Enter_x, Enter_y);
	}while(flag != true);	
	pf_map(pr, handle_out);
	
	while(1)
	{
		char ch;
		ch = getch();
		pos_pre = pos_now;
		if(ch == 0x1B) break;
		if(ch != 72 && ch != 80 && ch != 75 && ch != 77) continue;//up 72 down 80 left 75  rignt 77
		WriteConsoleOutputCharacter(handle_out, " ", 1, pos_now, &a);
			 
        	if(ch == 72) pos_now.Y--;
       	 	else if(ch == 80) pos_now.Y++;
        	else if(ch == 75) pos_now.X--;
        	else if(ch == 77) pos_now.X++;
        	if(pr[pos_now.Y - cor_x][pos_now.X - cor_y] != 0) pos_now = pos_pre;
		WriteConsoleOutputCharacter(handle_out, "*", 1, pos_now, &a);
		if(pos_now.X == posExit.X && pos_now.Y == posExit.Y)
		{
			printf("Win\n");
			system("pause");
			break;
		}
	}
	CloseHandle(handle_out);
	return 0;
	
}
