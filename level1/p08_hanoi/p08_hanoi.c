#include <stdio.h>
#define L 1
#define R 3
#define NUM 64
char wz[4][3]={"  ","左","中","右"};
int number[4]={0,NUM,0,0};

void fun(int from,int to,int num)
{

    if(num == 1){
        printf("%s->%s  ",wz[from],wz[to]);

        number[from]-=1;
        number[to]+=1;

        int i;
        for(i=1;i<=3;i++)
        {
            printf("%s:%d  ",wz[i],number[i]);
        }
        printf("\n");
        return;
    }

    else
    {
        int i;
        for(i=1;i<=3;i++)
            if(i!=from && i!=to)   break;
        fun(from,i,num-1);
        fun(from,to,1);
        fun(i,to,num-1);
    }
}

int main()
{
    int i;
    for(i=1;i<=3;i++)
    {
        printf("%s:%d  ",wz[i],number[i]);
    }
    printf("\n");

    fun (L,R,NUM);
    return 0;
}
