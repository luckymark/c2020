#include <stdio.h>
int main()
{
    int n,a=2,b;
    scanf("%d",&n);
    if(n==1){printf("no");}
    while(a<=n)
    {
        b=n%a;
        if(b==0&&a==n){printf("yes");break;}
        if(b==0&&a!=n){printf("no");break;}
        a+=1;
    }
    return 0;
}