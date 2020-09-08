#include <stdio.h>
#include <windows.h>
#include <time.h>
int main()
{
    int a,b,n;
    printf("2\n");
    for(n=3;n<=10000;n+=2)
    {
        a=2;
        if(n/2!=0)
        {
            while(a<=n)
            {
                b=n%a;
<<<<<<< HEAD
                if(b==0 && a==n){printf("%d\n",n);break;}
                if(b==0 && a!=n){break;}
=======
                if(b==0 && a==n)
                {
                    printf("%d\n",n);
                    break;
                }
                if(b==0 && a!=n)
                {
                    break;
                }
>>>>>>> d8d4165c6d1a6c4d5aa568cac24ba154e3e7026c
                a+=1;
            }
        }
        
    }
    long op,ed;
    op=clock();
    Sleep(1000);
    ed=clock();
    printf("%ldms\n",ed-op);
    return 0;
}