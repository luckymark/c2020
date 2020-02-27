#include<stdio.h>
#include <Windows.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>


char str[]="MiaoMiaoMiao";
//string to run
int len=strlen(str);

CONSOLE_SCREEN_BUFFER_INFO screen_info;
//windowAPI ,to get screen size in character

int i;
int main()
{
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//get stdout handle
int x_limit;
int left=0;
bool forward=true;
while(1){
	system("cls");
	
	GetConsoleScreenBufferInfo(hOut,&screen_info);
	x_limit=screen_info.dwSize.X;
	//get screeninfo
	
	for(i=0;i<left;++i)printf(" ");
	printf("%s",str);
	
	if(len+left==x_limit)forward=false;
	if(left==0)forward=true;
	
	if(forward)left++;
	else left--;
}

CloseHandle(hOut); 
return 0;
}
