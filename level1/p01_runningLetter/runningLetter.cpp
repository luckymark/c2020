#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
int main(void)
{
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
	CONSOLE_CURSOR_INFO cursor;
	DWORD a;
	COORD Str, End , Now, size;
	char s[1000];
	int len, i;
	
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &ConsoleInfo);

	
	Str.X = 0;
	Str.Y = 0;
	Now = Str;
	
	scanf("%s",s);
	len = strlen(s);
	
	GetConsoleCursorInfo(hOut, &cursor);
	cursor.bVisible = false;
	SetConsoleCursorInfo(hOut, &cursor);
	
//	printf("%d", ConsoleInfo.dwSize.X);
	
	while(true)
	{
		while(Now.X + len != ConsoleInfo.dwSize.X)
		{
			FillConsoleOutputCharacter(hOut, ' ', len, Now, &a);
			Now.X++;
			WriteConsoleOutputCharacter(hOut, s, len, Now, &a);
			Sleep(100);
		}
		while(Now.X >= 0)
		{
			FillConsoleOutputCharacter(hOut, ' ', len, Now, &a);
			Now.X--;
			WriteConsoleOutputCharacter(hOut, s, len, Now, &a);
			Sleep(100);
		}
	}
	return 0;
}
