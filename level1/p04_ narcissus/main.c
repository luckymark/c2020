#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    for(n=100;n<=999;n++)
    {
        int last = n % 10;
        int middle = (n/10)%10;
        int first = (n/100);
        if(n==pow(last,3)+pow(middle,3)+pow(first,3)) printf("%d\n",n);
    }
    return 0;
}
