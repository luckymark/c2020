#include<stdio.h>
#include<cmath>
#include<string.h>
char opt[20000];
void encrypt()
{
	
	printf("please enter the string you want to encrypt\n");
	scanf("%s",opt);
	for(int i=0;i<strlen(opt);i++)
	{
		opt[i]+=1;
	}
	printf("%s\n",opt);
	return;
}
void decrypt()
{
	printf("please enter the string you want to decrypt\n");
	scanf("%s",opt);
	for(int i=0;i<strlen(opt);i++)
	{
		opt[i]-=1;
	}
	printf("%s\n",opt);
	return;
}
int main()
{
	while(1)
	{
		memset(opt,0,sizeof(opt));
		printf("select the option\n");
		printf("1: encrypt a string\n");
		printf("2: decrypt a string\n");
		int jud;
		scanf("%d",&jud);
		if(jud==1) encrypt();
		else decrypt();
	}
}
