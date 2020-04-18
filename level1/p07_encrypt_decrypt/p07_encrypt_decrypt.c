#include <stdio.h>//都是一个函数，（偷懒
int main()
{
    char a[1000]={0};
    scanf("%[^\n]",a);
    int i=0,j;
    while(a[i]!=0||a[i+1]!=0)
    {
        i+=1;
    }
    for(j=0;j<i;j++)
    {
        a[j]=255-a[j];
    }
    for(j=i-1;j>=0;j--)
    {
        printf("%c",a[j]);//简陋的反着打印
    }
    return 0;
}