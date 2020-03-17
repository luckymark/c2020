#include<stdio.h>
#include<string.h>
#define MAX 50000
#define STEP 7
char res[MAX],message[MAX];

int letter_not(char a)
{
	if(a>='a' && a<='z')  return 1;
	if(a>'A' && a<='Z')   return 2;
	return 0;
}
char deal(char a)
{
	if(letter_not(a)==0)  return a;
	int st;
	if(letter_not(a)==1) st='a';
	else   st='A';
}
char encrypt(char a)
{

	char st=deal(a);
	int tran=a-st;
	tran=(tran+STEP)%26;
	return tran+st;	
}
char decrypt(char a)
{
	char st=deal(a);	
	int tran=a-st;
	tran=(tran+26-STEP)%26;
	return tran+st;		
}
int main()
{
	char c,s[15];
	int flag,i;

	gets(s);   //input 'encrypt' or 'decrypt' to execute this code 
	if(s[0]=='e')  flag=1;
	else  flag=0;
	
	gets(message);
	int len=strlen(message);
	
	for(i=0;i<=len-1;i++)
	{
		if(flag)  res[i]=encrypt(message[i]);
		else   res[i]=decrypt(message[i]);
	}
	printf("%s",res);
	return 0;
}
