#include <stdio.h>
#include <string.h>
const int BIGNUMBER = 100001;
char password[11] = "password";
//�޷���������
//ֻ�ܼ��ܽ���Сд��ĸ���޷����ܴ�д��ĸ�����֣��Լ�����
void encrypt(unsigned char s[]){
    char key[11];
    memcpy(key,password, sizeof(password));
    int lkey = strlen(key);
    for (int i = 0; i <strlen(s) ; ++i)
    {
        s[i] +=key[i%lkey]-'a'+1;   //charֻ��8bite ����127�ͻ��������s[]������ֻ����unsigned char
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
    printf("���ģ�%s\n",s);

    encrypt(s);
    printf("���ģ�%s\n",s);

    printf("���������룺\n");
    i=0;
    while((c=getchar()) != '\n')
        key[i++] = c;

    decrypt(s,key);
    printf("����������������%s",s);

    return 0;
}
