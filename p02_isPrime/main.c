#include <stdio.h>
#include <math.h>
int main()
{
    int n;
    printf("����һ������Ȼ���һ���������ǲ�������:");
    scanf("%d",&n);
    for (int i = 2; i <=sqrt(n) ; ++i)
        if( !(n%i) )
        {
            printf("��������");
            return 0;
        }
    printf("������");
    return 0;
}