#include <stdio.h>
#include <string.h>

void encrypt(char str[], int n)
{
    for (int i = 0; i < n; i++)
    {
        str[i] += i;
    }
    printf("\nYour password after encrypted was %s\n", str);
}

void decrypt(char str[], int n)
{
    for (int i = 0; i < n; i++)
    {
        str[i] -= i;
    }
    printf("\nYour password after decrypted was %s\n", str);
}

void options(void)
{
    printf("Please choose from these following options:\n");
    printf("a.encrypt\nb.decrypt\nc.quit\nYour option:");
}
int main()
{
    char password[20] = {'\0'};
    char flag;
    int en = 0, de = 0;                                                                       //表示密码加密和解密的次数
    printf("Please enter your password(length less than 20 characters):\n");
    scanf("%s", &password);
    while (getchar() != '\n');
    int length = strlen(password);
    while (1)
    {
        options();
        scanf("%c", &flag);
        while (getchar() != '\n');
        if (flag == 'a')
        {
            encrypt(password, length);
            en++;
            printf("Your password was encrypted %d times\n\n", en);
        }
        else if (flag == 'b')
        {
            decrypt(password, length);
            de++;
            printf("Your password was decrypted %d times\n\n", de);
        }
        else if (flag == 'c')
            break;
        else
            printf("Sorry,I can't understand your speaking...\nplease try it again\n");
    }
    printf("Bye!\n");
    getchar()
}
