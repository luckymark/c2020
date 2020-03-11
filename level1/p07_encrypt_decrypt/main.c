#include <stdio.h>
#include <stdlib.h>
void encrypt(char*);//加密函数
void decrypt(char*);//解密函数
int main() {
    /*读取任意长度的字符串*/
    int N = 1;
    char *p = (char*)malloc(N * sizeof(char));
    while (1)
    {
        p[N-1] = getchar();
        if (p[N-1] == '\n')
        {
            p[N-1] = '\0';
            break;
        } else{
            p = (char*)realloc(p, (++N) * sizeof(char));
        }
    }
    encrypt(p);
    printf("%s\n", p);
    decrypt(p);
    printf("%s", p);
    return 0;
}

void encrypt (char * p){
    int i = 0;
    while (p[i] != '\0')
    {
        p[i] = p[i] + (i + 1);
        i++;
    }
}

void decrypt (char * p){
    int i = 0;
    while (p[i] != '\0')
    {
        p[i] = p[i] - (i + 1);
        i++;
    }
}
