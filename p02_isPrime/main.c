#include <stdio.h>
#include <math.h>
int main()
{
    int n;
    printf("输入一个数，然后我会告诉你它是不是素数:");
    scanf("%d",&n);
    for (int i = 2; i <=sqrt(n) ; ++i)
        if( !(n%i) )
        {
            printf("不是素数");
            return 0;
        }
    printf("是素数");
    return 0;
}