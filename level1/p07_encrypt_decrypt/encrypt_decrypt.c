#include<stdio.h>
#include<stdlib.h>
#define MAX_LENGTH 100

char content[MAX_LENGTH] = "";
char password[MAX_LENGTH] = "";
int content_length = 0;
int pass_length = 0;

void encrypt();
void decrypt();
char virginia(char opt,char pass);
char initVector();
void inputContentAndPass();

/*
To ensure the security£¬stream encryption of CBC
(Cipher Block Chaining) mode is considered.
Unit encryption method is Virginia ALG,
to be instead once senior ALG is learnt.
*/

int main()
{	
	//show tips
	printf("Please select an option: \n1. Encrypt \n2. Decrypt \n");
	int index = 0;
	scanf("%d",&index);
	getchar();
	
	//get content,pass, and their length
	inputContentAndPass();
	
	//error check
	if(0 == content_length || 0 == pass_length || content_length < pass_length)
	{
		printf("Input error! ");
		getchar();
		return -1;
	} 
	 
	//jump over 
	if(1 == index)
	{
		encrypt();
		printf("Encrypted content is: ");
	}
		
	else if(2 == index)
	{
		decrypt();
		printf("Decrypted content is: ");
	}
		
	else
	{
		printf("Input Error! \n");
		return -1;
	}
	
	
	printf("\n%s\n\nProcess succeeded!\n",content);
	getchar();
	return 0;
}

void inputContentAndPass()
{
	int i = 0;
	
	//get content
	printf("\nPlease input your content: \n");
	scanf("%s",&content);
	for(i = 0;i < MAX_LENGTH;i++)
		if('\0' == content[i])
		{
			content_length = i+1;
			break;	
		}	
	
	getchar();
	
	//get password
	printf("\nPlease input your password: \nRemember your password can NOT be longer than your content \n");
	scanf("%s",&password);
	for(i = 0;i < MAX_LENGTH;i++)
		if('\0' == password[i])
		{
			pass_length = i+1;
			break;	
		}
}

void encrypt()
{
	//init, show second pass
	int i = 0;
	char tmpContent = initVector();
	printf("\nPlease remember your second password: %d, otherwise your data could be lost forever!\n",tmpContent);
	
	//CBC encrypt
	char tmpPass = 0;
	for(i = 0;i < content_length; i++)
	{
		tmpPass = password[i % pass_length];
		content[i] = content[i] ^ tmpContent;
		content[i] = virginia(content[i],tmpPass);
		tmpContent = content[i];
	}
	
}

void decrypt()
{
	//get iv
	char IV = 0;
	int tmpIV = 0;
	printf("\nPlease input your second password: ");
	scanf("%d",&tmpIV);
	IV = (char)tmpIV;
	printf("\n");
	
	//decrypt
	int i = 0;
	char tmpPass = 0;
	for(i = content_length - 1;i > 0; i--)
	{
		tmpPass = (-1) * password[i % pass_length];
		content[i] = virginia(content[i],tmpPass);
		content[i] = content[i] ^ content[i-1];
	}
	tmpPass = (-1) * password[0];
	content[0] = virginia(content[0],tmpPass);
	content[0] = content[0] ^ IV;
}

char virginia(char opt,char pass)
{
	return opt + pass;
}

char initVector()
{
	//get random initial vector
	srand((unsigned)time(NULL));
	int tmp = rand() % 256 - 128;
	char result = (char)tmp; 
	return result;
}
