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
                if(b==0 && a==n)
                {
                    printf("%d\n",n);
                    break;
                }
                if(b==0 && a!=n)
                {
                    break;
                }
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