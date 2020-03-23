#include <stdio.h>
#include <math.h>
int main()
{
    int n,m,i=0,a,b,c;
    for(m=100;m<=999;m++)
    {
        n=m;
        a =n%10,a=pow(a,3);
        n /=10;
        b =n%10,b=pow(b,3);
        n /=10;
        c =n%10,c=pow(c,3);
        
        if((a+b+c) == m)
        {
            printf("%d\n",m);
        }
    }
    return 0;
}