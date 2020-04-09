#include <stdio.h>
#include<string.h>
#define  MAXLEN 1000

int mode=-1;
inline void printReadMe();
inline void encode(char*);
inline void decode(char*);

int main() {
    printReadMe();
    char words[MAXLEN+1];
    while(~scanf("%d",&mode)){
        if(-1==mode)return 0;
        scanf("%s",words);
        if(1==mode){
            encode(words);
        }
        if(0==mode){
            decode(words);
        }
    }
    return 0;
}
inline void printReadMe(){
    system("cls");
    puts("****Usage****");
    puts("1 str : encode str");
    puts("0 str : decode str");
    puts("-1 : quit\n");
}
inline void encode(char *str){ 
    int i;
    for(i=0;i<strlen(str);++i){
        str[i]+=10;
        //shift 10
    }
    printf("encoded_str: %s\n\n",str);
}
inline void decode(char *str){ 
    int i;
    for(i=0;i<strlen(str);++i){
        str[i]-=10;
        //shift -10
    }
    printf("decoded_str: %s\n\n",str);
}
