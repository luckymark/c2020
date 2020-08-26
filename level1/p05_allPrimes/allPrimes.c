#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>
#define f(i,j,k) for(i=(j);i<=(k);i++)
const int maxn = 10000; int i,c,count;
c=0;
int main() {
    bool a[maxn + 5];
    int b[maxn+5];
    memset(a, true, sizeof(a));
    f(i, 2, maxn)
    {
        if (a[i]) b[c++]=i;
        for(int y=0;y<c&&i*b[y]<maxn;y++){
            a[i*b[y]]=false;
            if(0==i%b[y]) break;
        }
    }
    f(count,1,maxn-5){
        if(a[count]) printf("%d ",count);
    }
    return 0;
}