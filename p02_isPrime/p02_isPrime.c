#include <stdio.h>
#include <math.h>
int main()
{
    int n;
    printf("Input a number and I will tell you if it is prime:");
    scanf("%d",&n);
    for (int i = 2; i <=sqrt(n) ; ++i)
        if( !(n%i) )
        {
            printf("It is not prime");
            return 0;
        }
    printf("It is prime");
    return 0;
}