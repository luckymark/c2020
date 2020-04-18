#include <stdio.h>
#include <string.h>
#define KEY 2

char encrypt(char a)
{
    return (a + KEY) % 256;
}

char decrypt(char a)
{
    return (a - KEY + 256) % 256;
}

int main()
{
    char s[110];
    int size;
    scanf ("%s",s);
    size = strlen(s);

    int i;
    for(i=0;i<size;i++)
    {
       s[i]=encrypt(s[i]);
    }
    printf("%s\n",s);

    for(i=0;i<size;i++)
    {
        s[i]=decrypt(s[i]);
    }
    printf("%s\n",s);
}
