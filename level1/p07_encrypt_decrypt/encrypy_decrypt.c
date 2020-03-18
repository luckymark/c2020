#include <stdio.h>
#include <string.h>
#define maxn 1005

void encrtpt(char* s,int len) {  //加密 各位+1
    for(int i=0; i<=len-1; i++){
        int a =(int)(*(s+i))+1;
        printf("%c",(char)(a%128));
    }
    printf("\n");
}
void decrypt(char* s,int len) {  //解密 各位-1
    for(int i=0; i<=len-1; i++){
        int a =(int)(*(s+i))+127;
        printf("%c",(char)(a%128));
    }
    printf("\n");
}
int main() {
    char s[maxn]="!!!!!";
    int len = strlen(s);
    encrtpt(s,len);
    decrypt(s,len);
}
