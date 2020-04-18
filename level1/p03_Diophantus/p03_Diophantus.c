#include <stdio.h>
int main()
{
    float m=0;
    while(1)
    {
        m += 1;
        if((1.0/6 + 1.0/12 + 1.0/7 + 1.0/2)*m + 4 + 5 ==m)
        {
            printf("%.f",m-4);
            break;
        }
    }
    return 0;
}