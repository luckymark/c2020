#include<stdio.h>
#include<string.h> 
void  encrypt (char *a);
void  decrypt (char *b);
int main()
{
	int t;
	char a[1000000];
	scanf("%s",a);
	printf("你是否想要加密？（请输入1表示想，0表示不想）");
	scanf("%d",&t);
	if(t==1){
	encrypt(a);	
	}
	printf("你是否想要解密？（请输入1表示想，0表示不想）");
	scanf("%d",&t);
		if(t==1){
	decrypt(a);
	}    

      return 0;
}

void encrypt (char *a)
{
	int num;
	for (num=0; num<strlen(a);num++){
			if(a[num]==126){
		a[num]=20;
		printf("%c",a[num]);
	}else{
			a[num]=a[num]+1;
			printf("%c",a[num]);
	}

	}
	printf("\n");
	
}

	
void decrypt (char *b)
{
	int num;
	for (num=0; num<strlen(b);num++){

	if(b[num]==20){
		b[num]=126;
		printf("%c",b[num]);
	}else{
			b[num]=b[num]-1;
			printf("%c",b[num]);
	}
	
		
	}
	printf("\n");
} 



