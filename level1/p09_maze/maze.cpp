#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

const int Len = 30;
const int Height = 10;//
const int cor_x = 6;
const int cor_y = 6;


int main()
{
	srand(time(0));
	FILE *fin;
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	CHAR_INFO chFill;
	SMALL_RECT pos_move;
	COORD posText;
	COORD posEnter;
	COORD posExit;
	COORD pos_now;
	COORD pos_pre;
	DWORD a;
	int i,lim_up,lim_down,lim_left,lim_right;
	int pr[50][50];
	
	GetConsoleCursorInfo(handle_out, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle_out, &CursorInfo);
	
	
	posText.X = cor_y;
	posText.Y = cor_x;
	
 	posEnter = posText;
	posEnter.X++;
	
	posExit.X += Len - 1;
	posExit.Y += Height;
	
//	pos_move.Left = pos_move.Right = posEnter.X;
// 	pos_move.Top = pos_move.Bottom = posEnter.Y;
 	
 	pos_now = posEnter;
 	
// 	lim_up = cor_x;
// 	lim_down = cor_x + Height;
// 	lim_left = cor_y;
// 	lim_right = cor_y + Len;
 	
	
	FillConsoleOutputCharacter(handle_out, '-', Len, posText, &a);
	
	WriteConsoleOutputCharacter(handle_out, "+", 1, posText, &a);
	
	FillConsoleOutputCharacter(handle_out, '*', 1, posEnter , &a);
	
	if((fin = fopen("map.txt","r")) != NULL)
	{
		int i,j;
		for(i = 1;i <= Height;i++)
		{
			char s[100];
			scanf("%s",s+1);
			for(j = 1;j <= Len;j++)
			if(s[j] == ' ') pr[i][j] = 1;
			else pr[i][j] = 0;
		}
	}
	else
	{
		for(i = 1;i <= 10;i++)
		{
		posText.Y++;
		FillConsoleOutputCharacter(handle_out, '|', 1, posText, &a);
		COORD pos_maze = posText;
		int j;
		for(j = 1;j <= 28;j++)
		{
			pos_maze.X++;
			char *c;
			int x = rand() %10;
			if(x >= 8)
			c = "x",
			pr[i][j] = 0;
			else 
			c = " ",
			pr[i][j] = 1;
			WriteConsoleOutputCharacter(handle_out, c, 1, pos_maze, &a);
		}
		}
	}
	
	
	posText.Y++;
	WriteConsoleOutputCharacter(handle_out, "+", 1, posText, &a);
	posText.X++;
	for(i = 1;i <= Len - 2;i++)
	{
		posText.X++;
		FillConsoleOutputCharacter(handle_out, '-', 1, posText, &a);
	}
	
	WriteConsoleOutputCharacter(handle_out, "+", 1, posText, &a);
	posText.X--;
	pr[posText.Y - cor_y][posText.X - cor_x] = 1;
	posExit = posText;
	WriteConsoleOutputCharacter(handle_out, " ", 1, posText, &a);
	posText.X++;
	for(i = 1;i <= Height;i++)
	{
		posText.Y--;
		FillConsoleOutputCharacter(handle_out, '|', 1, posText, &a);
	}
	posText.Y--;
	WriteConsoleOutputCharacter(handle_out, "+", 1, posText, &a);
	
	while(1)
	{
		char ch;
		ch = getch();
		pos_pre = pos_now;
		if(ch == 0x1B) break;
		if(ch != 72 && ch != 80 && ch != 75 && ch != 77) continue;
		WriteConsoleOutputCharacter(handle_out, " ", 1, pos_now, &a);
//		if(ch == 72 && (pos_now.Y - 1> lim_up || (pos_now.Y - 1 == 6 && pos_now.X == 6)))//up 72 down 80 left 75  rignt 77
//			  pos_now.Y--;
//
//		else if(ch == 80 && 
//		(pos_now.Y + 1< lim_down || (pos_now.X == posExit.X && pos_now.Y + 1 == posExit.Y)))
//			 pos_now.Y++;
//		else if(ch == 75 && pos_now.X - 1 > lim_left)
//			 pos_now.X--;
//	    else if(ch == 77 && pos_now.X + 1 < lim_right)
//	    	 pos_now.X++;
			 
        if(ch == 72) pos_now.Y--;
        else if(ch == 80) pos_now.Y++;
        else if(ch == 75) pos_now.X--;
        else if(ch == 77) pos_now.X++;
        
		if(pr[pos_now.Y - cor_x][pos_now.X - cor_y] != 1) pos_now = pos_pre;
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
