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
int main(void)
{
	while(1)
	{
		system("cls");
		printf("ÇëÑ¡ÔñÒªÊµÏÖµÄ¹¦ÄÜ\n");
		printf("1¼ÓÃÜ×Ö·û´®\n");
		printf("2½âÃÜ×Ö·û´®\n");
		char c;
		c = getch();
		if(c != '1' && c!= '2') continue;
		if(c == '1')
		printf("ÇëÊäÈëÒª¼ÓÃÜµÄ×Ö·û´®\n");
		else if(c == '2')
		printf("ÇëÊäÈëÒª½âÃÜµÄ×Ö·û´®\n");
		char s[200];
		scanf("%s",s);
		if(c == '1')
		encrypt(s);
		else decrypt(s);
		printf("\nÇë°´ÈÎÒâ¼ü¼ÌÐø");
		char ch = getch();
	}
	return 0;
}
