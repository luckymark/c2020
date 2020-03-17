#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define LENGTH 30
int main(){
	int i=0,count=0,t=1;
	while(1){
		for(i=0;i<count;i++){
			printf(" ");
		}
		if(count<LENGTH&&t==1){
			count++;
		}else{
			count--;
			t=0;
			if(count==0){
				t=1;
			}//改动让H无限循环跑下去 
		}
		printf("H");
		Sleep(40);
		system("cls");
	}
	return 0;
}
