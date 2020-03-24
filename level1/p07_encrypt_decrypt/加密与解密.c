#include <stdio.h>
#include <string.h>
void jiami(char * a,int l_1);
void jiemi(char * b,int l_2); 
int main()
 {	
	
	char c[999999];
	gets(c);
	int l=strlen(c);
	jiami(c,l);
	jiemi(c,l);
	return 0;
 } 
void jiami(char * a,int l_1)
 {
 	int i;
 	printf("º”√‹£∫"); 
	 for(i=0 ; i<l_1 ; ++i)
	 {
	 	a[i] = a[i] + 2 ;
	 }
	 printf("%s",a);
 }
 
void jiemi(char *b,int l_2)
{
	int j;
	printf("\nΩ‚√‹£∫");
	for(j=0 ; j<l_2 ; ++j)
	{
		b[j] = b[j] - 2;	
	} 
	printf("%s",b);		
} 
