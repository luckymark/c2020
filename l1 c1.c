#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define length 30
int main(){
	int i=0,count=0,t=1;
	while(1){
		for(i=0;i<count;i++){
			printf(" ");
		}
		if(count<length&&t==1){
			count++;
		}else{
			count--;
			t=0;
		}
		printf("H");
		Sleep(40);
		system("cls");
	}
	return 0;
}
