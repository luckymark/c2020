#include<stdio.h>
#include <Windows.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

HANDLE hOut;
//stdout's handle

CONSOLE_SCREEN_BUFFER_INFO screen_info;
//screen's size in character

int len=-1;
int xLimit=-1;
int leftDis=0;
bool forward=true;

inline HANDLE getStdHandle(){ 
    //get stdout handle
    HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
    if(NULL==handle){ 
        printf("Error: Cann't get stdout handle\n");
        exit(-1);
    }
    return handle;
}
inline void updateXLimit(){ 
    GetConsoleScreenBufferInfo(hOut,&screen_info);
    //get screeninfo
    xLimit=screen_info.dwSize.X;
    //get width in chars
}
void updateMove();
void run(char *);

int main()
{
    hOut=getStdHandle();
    run("MiaoMiaoMiao");
    CloseHandle(hOut); 
    return 0;
}
void run(char *str){ 
    len=strlen(str);
    while(1){
        system("cls");
        //clean screen

        updateXLimit();
        //get width(resizable)

        int i;
        for(i=0;i<leftDis;++i)printf(" ");
        printf("%s",str);
        //show words

        updateMove();
        //update move policy
    }
}
void updateMove(){ 
    if(len+leftDis==xLimit)forward=false;
    if(leftDis==0)forward=true;
    //reorient

    if(forward)leftDis++;
    else leftDis--;
    //update left margin
}
