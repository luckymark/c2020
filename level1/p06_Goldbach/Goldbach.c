#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>
#define f(i,j,k,s) for(i=(j);i<=(k);i+=s)
const int maxn = 105; int i,c,count,count1;
c=0;
int main() {
    bool a[maxn + 5];bool check[maxn+5];
    int b[maxn+5];
    memset(a, true, sizeof(a));
    memset(check,false,sizeof(check));
    f(i, 2, maxn,1)
    {
        if (a[i]) b[c++]=i;
            for(int y=0;y<c&&i*b[y]<maxn;y++){
                a[i*b[y]]=false;
                if(0==i%b[y]) break;
            }
    }
    f(count,1,100,1)
        f(count1,2,100,1){
        check[count+count1]=true;
    }
    f(count,4,100,2){
        if(false==check[count]) {
            puts("wrong");
            return 0;
        }
    }
    puts("right");
    return 0;
}