#include <stdio.h>
void hanoi(char a,char b,char c,int n)
{
    if(n == 1)
        printf("%c->%c\n",a,c);
    if(n > 1)
    {
        hanoi(a,c,b,n-1);
        hanoi(a,b,c,1);
        hanoi(b,a,c,n-1);
    }
}

int main() {
    hanoi('A','B','C',64);
    return 0;
}
