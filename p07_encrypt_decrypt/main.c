#include <stdio.h>
#include <string.h>
const int BIGNUMBER = 100001;
char password[11] = "password";
//无法设置密码
//只能加密解密小写字母，无法加密大写字母，数字，以及符号
void encrypt(unsigned char s[]){
    char key[11];
    memcpy(key,password, sizeof(password));
    int lkey = strlen(key);
    for (int i = 0; i <strlen(s) ; ++i)
    {
        s[i] +=key[i%lkey]-'a'+1;   //char只有8bite 超过127就会溢出，故s[]的类型只能是unsigned char
        if(s[i]>'z')
            s[i]=s[i]+'a'-'z'-1;
    }
}

void decrypt(unsigned char s[],char key[]){
    int lkey = strlen(key);
    for (int i = 0; i <strlen(s) ; ++i) {
        s[i]-=key[i%lkey]-'a'+1;
        if(s[i]<'a')
            s[i]+='z'-'a'+1;

    }

}
int main() {
    unsigned char s[BIGNUMBER];
    char c ,key[11];

    int i=0;
    while((c=getchar()) != '\n')
        s[i++] = c;
    printf("密文：%s\n",s);

    encrypt(s);
    printf("明文：%s\n",s);

    printf("请输入密码：\n");
    i=0;
    while((c=getchar()) != '\n')
        key[i++] = c;

    decrypt(s,key);
    printf("根据密码解出的密文%s",s);

    return 0;
}
