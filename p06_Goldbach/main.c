#include <stdio.h>
#include <math.h>

const int MAXN=100;
int isprime(int x)
{
    for (int i = 2; i < sqrt(x); ++i) {
        if(x%i == 0)
            return 0;
    }
    return 1;
}
int main()
{
    int times=0,cnt=0;
    for (int i = 4; i <=MAXN ; i+=2) {
        times++;
        for (int j = 2; j <=i ; ++j)
        {
            if( isprime(j) && isprime(i-j)){
                cnt++;
                break;
            }
        }
    }
    if(cnt == times) printf("100���ڸ�°ͺղ������");
    else printf("100���ڸ�°ͺղ��벻����");
    return 0;
}
