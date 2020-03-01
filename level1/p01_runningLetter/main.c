#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>

#define WIDTH 60

int main()
{
    char kin[10];
    int i, j = 0;
    int flag = 1;
    printf("Please enter a word or letter:");
    scanf("%s", kin);
    int len = strlen(kin);
    while (1)
    {
        for (i = 0; i < j; i++)
        {
            printf(" ");
        }
        printf("%s",kin);
        system("CLS");
        Sleep(0.1);
        if (j == 0) flag = 1;
        else if (j == WIDTH - len) flag = -1;
        j += flag;
    }
    return 0;
}