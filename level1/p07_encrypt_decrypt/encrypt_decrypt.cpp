#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int maxLength=1000;
void encrypt(char *str)
{
	int len=strlen(str);
	printf("the result:\n");
	for(int i=len-1;i>=0;i--)
	{
		if(str[i]<='Z'&&str[i]>='A') printf("%c",'Z'-str[i]+'a');
		else if(str[i]<='z'&&str[i]>='a') printf("%c",'z'-str[i]+'A');
		else if(str[i]<='9'&&str[i]>='0') printf("%c",(str[i]-'0'+8)%10+'0');
		else printf("%c",str[i]);
	}
	printf("\n");
}
void decrypt(char *str)
{
	int len=strlen(str);
	printf("the result:\n");
	for(int i=len-1;i>=0;i--)
	{
		if(str[i]<='Z'&&str[i]>='A') printf("%c",'Z'-str[i]+'a');
		else if(str[i]<='z'&&str[i]>='a') printf("%c",'z'-str[i]+'A');
		else if(str[i]<='9'&&str[i]>='0') printf("%c",(str[i]-'0'+2)%10+'0');
		else printf("%c",str[i]);
	}
	printf("\n");
}
int main()
{
	char str[maxLength];
	printf("please input the string:\n");
	scanf("%s",str);
	printf("encrypt/decrypt?\n");
	char order[100];
	scanf("%s",order);
	if(strcmp(order,"encrypt")==0) encrypt(str);
	else if(strcmp(order,"decrypt")==0) decrypt(str);
	else printf("error!!\n");
	return 0;
}
