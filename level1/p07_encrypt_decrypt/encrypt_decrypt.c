#include <stdio.h>
#include <string.h>
#define MAXN 10000   //字符串最大值

int keyLen,strLen;
int len = 136 -32 + 1;  //ascii码中可显示字符的个数
char key[20];
char str[MAXN]; //32~136

//把字符a改变成右移n的字符（n>0)
void changeChar(char* a, int n){
    int b = 32 + (*a - 32 + n) % len; //在区间内循环
    *a = (char)b;
}

//加密
void encrypt(){
    int j = 0;
    for (int i = 0; i < strLen; ++i) {
        changeChar(&str[i],key[j]);
        j = (j+1) % keyLen;
    }
}

//解密
void decrypt(){
    int j = 0;
    for (int i = 0; i < strLen; ++i) {
        changeChar(&str[i],len - key[j]);
        j = (j+1) % keyLen;
    }
}

int main(){
    //输入
    int flag;
    puts("Want to encrypt or decrypt?");
    puts("0 -- encrypt");
    puts("1 -- decrypt");
    flag = (getchar() - '0');

    gets(key);
    puts("\nPlease input the key(less than 20)");
    gets(key);
    keyLen = (int)strlen(key);
    puts("\nPlease input the text");
    gets(str);
    strLen = (int)strlen(str);

    if(flag){
        decrypt();
    }else{
        encrypt();
    }

    puts("\nThe string is:");
    puts(str);

    return 0;
}
