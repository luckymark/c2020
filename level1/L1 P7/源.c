#include<stdio.h>
#include<string.h>
#pragma warning(disable : 4996)
void encryption(char str[]) {
	int j = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] += j;
		j++;
		if (j == 5)
			j = 0;
	}
}

void decryption(char str[]) {
	int j = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] -= j;
		j++;
		if (j == 5)
			j = 0;
	}
}

int main(void)
{
	char str[100];
	scanf("%s", &str);
	encryption(str);
	printf("%s\n", str);
	decryption(str);
	printf("%s", str);
	return 0;
}