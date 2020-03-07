#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
int strlength(char* s)
{
	if(s == NULL) return 0;
	int cnt = 0;
	char ch;
	do
	{
		ch = *(s + cnt);
		cnt++;
	}while(ch != '\0' && ch != ' ' && ch != '\n' && ch != '\t');
	return cnt - 1;
}
void encrypt(char* s)
{
	int len = strlength(s);
	int i;
	printf("加密后的字符串为\n");
	for(i = 0;i < len;i++)
		printf("%c",*(s + i) + 1 + i / 2);
	return;
}
void decrypt(char* s)
{
	int len = strlength(s);
	int i;
	printf("原的字符串为\n");
	for(i = 0;i < len;i++)
		printf("%c", *(s + i) - 1 - i / 2);
}
int main(void)
{
	while(1)
	{
		system("cls");
		printf("请选择要实现的功能\n");
		printf("1加密字符串\n");
		printf("2解密字符串\n");
		char c;
		c = getch();
		if(c != '1' && c!= '2') continue;
		if(c == '1')
			printf("请输入要加密的字符串\n");
		else if(c == '2')
			printf("请输入要解密的字符串\n");
		char s[200];
		scanf("%s",s);
		if(c == '1')
			encrypt(s);
		else 
			decrypt(s);
		printf("\n请按任意键继续");
		char ch = getch();
	}
	return 0;
}
