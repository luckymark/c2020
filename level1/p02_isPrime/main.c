#include <stdio.h>
#include<math.h>

int main()
{

    printf("请输入一个正整数：");
    fflush(stdout);
    int sherry,i;
    scanf("%d",&sherry);
    int sqr=sqrt(sherry);
    if(sherry==1)
    {
        printf("不是素数！");
        fflush(stdout);
    }
    else if(sherry>=2)
    {
        for(i=2;i<=sqr;i++)
        {
            if(sherry%i == 0)
                break;
        }
        if(i==sqr+1)
        {
            printf("是素数！");
            fflush(stdout);
        }
        else
        {
            printf("不是素数！");
            fflush(stdout);
        }

    }
    else
    {
        printf("输入格式错误！");
        fflush(stdout);
    }
    return 0;
}
