#include <stdio.h>

#define NUMBER 64        //the number of the disks.
/*  The number of disks from top to bottom is 1~64.*/

void move(char a,char b,char c,int n) /*a is the original column,b is the middle disk,
 c is the target disk,n is the number of moving disks.*/
{
    if(n==1)
    {
        printf("move the %2dst disk: %c -> %c\n",n,a,c);
    }
    else
    {
        move(a,c,b,n-1);
        printf("move the %2dst disk: %c -> %c\n",n,a,c);
        move(b,a,c,n-1);
    }
}

int main()
{
    move('a','b','c',NUMBER); //把64个圆盘从a移动到c。
    return 0;
}
