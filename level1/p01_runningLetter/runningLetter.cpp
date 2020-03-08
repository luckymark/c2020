#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#define For(x,a,b) for(x=a;x<=b;x++)
#define WIDTH 80
int i,i1,i2;
int main(void)
{
	char letter[865]="Microsoft";
	int flag,space;
	flag=1;
	space=0;
	while(1){
		For(i,0,space) printf(" ");
		space+=flag;
		printf("%s",letter);
		Sleep(50);
		system("CLS");
		if(space==WIDTH||space==0) flag=-flag;
	}
	return 0;
}
