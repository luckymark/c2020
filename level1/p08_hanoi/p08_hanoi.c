#include <stdio.h>
void tell(int a,char former,char later)
{
    printf("move %d from %c to %c\n",a,former,later);
}
void move(int all,char former,char helper,char later)
{
    if(all==1) tell(all,former,later);
    else
    {
        move(all-1,former,later,helper);
        tell(all,former,later);
        move(all-1,helper,former,later);
    }
}
int main()
{
    int n=4;
    char x='A',y='B',z='C';
    move(n,x,y,z);
    return 0;
}