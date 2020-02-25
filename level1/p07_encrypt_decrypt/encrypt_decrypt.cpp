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
	printf("¼ÓÃÜºóµÄ×Ö·û´®Îª\n");
	for(i = 0;i < len;i++)
	printf("%c",*(s + i) + 1 + i / 2);
	return;
}
void decrypt(char* s)
{
	int len = strlength(s);
	int i;
	printf("Ô­µÄ×Ö·û´®Îª\n");
	for(i = 0;i < len;i++)
	printf("%c", *(s + i) - 1 - i / 2);
}
