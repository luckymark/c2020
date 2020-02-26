#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
const int SLEEP_TIME = 10;
int main(void)
{
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
	CONSOLE_CURSOR_INFO cursor;
	DWORD a;
	COORD Now;
	char s[1000];
	int len, i;
	
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &ConsoleInfo);

	
	Now.X = 0;
	Now.Y = 0;
	
	scanf("%s",s);
	len = strlen(s);
	
	GetConsoleCursorInfo(hOut, &cursor);
	cursor.bVisible = false;
	SetConsoleCursorInfo(hOut, &cursor);
	
	
	while(true)
	{
		while(Now.X + len != ConsoleInfo.dwSize.X)
		{
			FillConsoleOutputCharacter(hOut, ' ', len, Now, &a);
			Now.X++;
			WriteConsoleOutputCharacter(hOut, s, len, Now, &a);
			Sleep(SLEEP_TIME);
		}
		while(Now.X >= 0)
		{
			FillConsoleOutputCharacter(hOut, ' ', len, Now, &a);
			Now.X--;
			WriteConsoleOutputCharacter(hOut, s, len, Now, &a);
			Sleep(SLEEP_TIME);
		}
	}
	return 0;
}
