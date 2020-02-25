#include<cstdio>
#include<stdlib.h>
#include<windows.h>
#include<cstring>
 
const int SLEEP_TIME = 50;
const int CHANGE_TIME = 3;
const int WIDTH = 80;

int main(){
	
	for(int i = 0; i < CHANGE_TIME; i++){			
		char x[WIDTH-1];
		for(int j = 0; j <= WIDTH-1; j++){
			Sleep(SLEEP_TIME);
			system("CLS");
			for(int k = 0; k <= WIDTH-1; k++)
				x[k] = ' ';
			x[j] = 'A';
			printf(x);
		}
		for(int j = WIDTH-1;j >= 0;j--){
			Sleep(SLEEP_TIME);
			system("CLS");
 			for(int k = 0;k <= WIDTH-1; k++)
				x[k] = ' ';
			x[j] = 'A';	
			printf(x);
		}
	}
	return 0;
}
