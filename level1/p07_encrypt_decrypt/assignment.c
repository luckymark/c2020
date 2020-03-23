#include <stdio.h>
#include <stdlib.h>

#define MAX 999       //最大字符处理长度+1
#define upLim 126     //可处理字符串的右范围
#define downLim 32    //可处理字符串的左范围
#define processWay 5  //加密模式（右移多少位）

int getStr(char *str);
void encryptStr(char *str);
void decryptStr(char *str);
void printStr(char *str, int lenth);
void mainFunc(char *str);
//功能介绍：可以加解密的字符：大小写字母 空格 数字 符号

//得到输入的字符串,储存在数组str中,并返回字符串长度
int getStr(char *str) {
    char c;
    int i = 0;

    while ((c = getchar()) != '\n') {
        str[i++] = c;
    }
    return i;
}

//加密：每个字符ascii码+5（有循环）
void encryptStr(char *str) {
    puts("Please input the string that you want to ENCRYPT:");
    int lenth = getStr(str);
    int a = 0;  //超出边界的个数
    for (int i = 0; i < lenth; i++) {
        a = (str[i] + processWay) - upLim;
        if (a > 0) {
            str[i] = (downLim - 1) + a;
            continue;
        }
        str[i] += processWay;
    }
    system("cls");
    puts("The string encrypted is:");
    printStr(str, lenth);
}

//解码
void decryptStr(char *str) {
    puts("Please input the string that you want to DECRYPT:");
    int lenth = getStr(str);
    int a = 0;  //掉出边界的位置个数
    for (int i = 0; i < lenth; i++) {
        a = 10 - (str[i] - processWay);
        if (a > 0) {
            str[i] = (upLim + 1) - a;
            continue;
        }
        str[i] -= processWay;
    }
    system("cls");
    puts("The string decrypted is:");
    printStr(str, lenth);
}

//打印字符串并额外输出一个\n
void printStr(char *str, int lenth) {
    for (int i = 0; i < lenth; i++) {
        printf("%c", str[i]);
    }
    puts("");
}

//
void mainFunc(char *str) {
    int choice;
    while (1) {
        choice = 0;
        puts("-------------------------------------------------------------");
        puts("Please input the corresponding number that process you want:");
        puts("1 Encrypt a string");
        puts("2 Decrypt a code");
        puts("3 Quit");
        scanf("%d", &choice);
        fflush(stdin);
        switch (choice) {
            case 1:
                puts("-----------------------------");
                encryptStr(str);
                break;
            case 2:
                puts("-----------------------------");
                decryptStr(str);
                break;
            case 3:
                return;
                break;
            default:
                system("cls");
                puts("Please input a valid number!");
        }
    }
}

int main(void) {
    char str[MAX] = {0};
    mainFunc(str);
    return 0;
}