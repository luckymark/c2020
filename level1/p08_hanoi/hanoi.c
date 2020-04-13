#include <stdio.h>
int cnt=0;
void f(int n,char x,char y){
    if(n<1) return;
    f(n-1,'A','B');
    printf("%c->%c\n",x,y);
    cnt++;
    f(n-1,'B','C');
}
int main() {
    int n;
    scanf("%d",&n);
    f(n,'A','C');
    printf("%d",cnt);
    return 0;
}
