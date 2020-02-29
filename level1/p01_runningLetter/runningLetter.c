#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 80
const int TIME = 20;  //Majic Number

int main(){
    int flag = -1;
    int j = 0;
    for(;;j+=flag){
        for(int i=0;i<j;i++){
            printf(" ");
        }
        printf("A");
        Sleep(TIME);
        system("CLS");

        if(j==WIDTH||j==0) flag=-flag;
    }
    return 0;
    
}