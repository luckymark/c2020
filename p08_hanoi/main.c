#include <stdio.h>
#include <time.h>

int cnt = 0;
//从a移到b,中转c
void hannoi(int x,char a,char b,char c)
{
    if (x==1){
        printf("a-->b\n");
        cnt=1;
        return;
    }
    if(x==2)
    {
        printf("%c-->%c\n",a,c);
        printf("%c-->%c\n",a,b);
        printf("%c-->%c\n",c,b);
        cnt+=3;
        return ;
    }

    hannoi(x-1,a,b,c);
    printf("%c-->%c\n",a,c);
    cnt++;
    hannoi(x-1,b,c,a);


}
int main() {
    clock_t start,end;
    start=clock();
    hannoi(4,'a','b','c');
    end=clock();
    double total_time = (double)(end-start)/CLOCKS_PER_SEC;
    printf("All is done in %.3lfs with %d steps.",total_time,cnt);
    return 0;
}