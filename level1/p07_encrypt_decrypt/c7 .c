#include<stdio.h>
#include<string.h>
#define MAXN 1001
#define KEY 5
void encrypt(char* p, int len);
void decrypt(char* p, int len);
int main() {
	char p [MAXN];
	scanf("%s", p);
	int len;
	len = strlen(p);
	char* p1;
	p1 = &p[0];
	encrypt(p1, len);
	printf("加密后的字符：%s\n", p);
	decrypt(p1, len);
	printf("解密后的字符：%s\n", p);
}
void encrypt(char* p, int len) {
	for (int i = 0; i < len; i++)
		{
			*(p+i) = *(p+i) + KEY;
		}
}
void decrypt(char* p, int len) {
	for (int i = 0; i < len; i++)
	{
		*(p + i) = *(p + i) - KEY;
	}
}