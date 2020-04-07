#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#pragma warning(disable : 4996)

#define LENGTH 50								//长度
#define SET_CON "mode con cols=50 lines=10"		//设置控制台宽度和高度

void show(char str[])							//输入完空格之后打印字符
{
	printf("%s", str);
	Sleep(10);
	system("cls");
}
int main(void)
{
	char str[100];
	system(SET_CON);
	scanf("%s", &str);							//写的时候以为是自己输入字符
	int len = strlen(str);
	while (1) {
		for (int i = 0; i < LENGTH - len; i++)
		{
			for (int j = 0; j <= i; j++)
				printf(" ");
			show(str);
		}
		for (int i = 0; i < LENGTH - len; i++)
		{
			for (int j = LENGTH - len - i; j > 0; j--)
				printf(" ");
			show(str);
		}
	}
	return 0;
}