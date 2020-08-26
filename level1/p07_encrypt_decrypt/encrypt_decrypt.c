//先写了一遍，然后git add之后忘记git commit直接push了，后来不知道干了啥本地代码就不见了。。
//然后就重写了一遍。。自闭了呜呜呜，还好这个比较简单
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encrypt(char *str,char *dark){
    int i;
    for(i=0;*(str+i)!='\0';i++){
        if(*(str+i)>='a'&&*(str+i)<='z'){
            *(dark+i)='a'+'z'-*(str+i);
        }else if(*(str+i)>='A'&&*(str+i)<='Z'){
            *(dark+i)='A'+'Z'-*(str+i);
        }else *(dark+i)=*(str+i)+3;
    }
}

void decrypt(char *str,char *clear){
    int i;
    for(i=0;*(str+i)!='\0';i++){
        if(*(str+i)>='a'&&*(str+i)<='z'){
            *(clear+i)='a'+'z'-*(str+i);
        }else if(*(str+i)>='A'&&*(str+i)<='Z'){
            *(clear+i)='A'+'Z'-*(str+i);
        }else *(clear+i)=*(str+i)-3;
    }
}

int main(){
    char *str=(char*)malloc(sizeof(char)),*clear=(char*)malloc(sizeof(char)),*dark=(char*)malloc(sizeof(char));
    gets(str);
    encrypt(str,dark);
    puts(dark);
    decrypt(dark,clear);
    puts(clear);
    if(!strcmp(str,clear)){
        printf("true\n");
    }else printf("false\n");
    return 0;
}