#include <stdio.h>
#include<string.h>
#include<stdlib.h>

#define LEN 100

void inzhan(int m);

void outzhan(void);

int zhan[LEN];

char op[LEN][LEN];

int len=0,n=0;

int main() {
    while(scanf("%s",op[len])==1)
    {
        len++;
    }
    for(int i=len-1;i>=0;i--)
    {
        if(strcmp(op[i],"+")==0)
        {
            zhan[n-2]=zhan[n-2]+zhan[n-1];
            n--;
        }
        else if(strcmp(op[i],"-")==0)
        {
            zhan[n-2]=zhan[n-1]-zhan[n-2];
            n--;
        }
        else
        {
            inzhan(atoi(op[i]));
            n++;
        }
    }
    printf("%d",zhan[0]);
    getchar();

    return 0;
}
void inzhan(int m)
{
    zhan[n]=m;
}

void outzhan(void)
{
    len--;
}
