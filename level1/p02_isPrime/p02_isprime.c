#include <stdio.h>
<<<<<<< HEAD
=======
#include <math.h>
>>>>>>> d8d4165c6d1a6c4d5aa568cac24ba154e3e7026c
int main()
{
    int n,a=2,b;
    scanf("%d",&n);
    if(n==1){printf("no");}
    while(a<=n)
    {
        b=n%a;
<<<<<<< HEAD
        if(b==0&&a==n){printf("yes");break;}
        if(b==0&&a!=n){printf("no");break;}
=======
        if(b==0&&a==n)
        {
            printf("yes");
            break;
        }
        if(b==0&&a!=n)
        {
            printf("no");
            break;
        }
>>>>>>> d8d4165c6d1a6c4d5aa568cac24ba154e3e7026c
        a+=1;
    }
    return 0;
}