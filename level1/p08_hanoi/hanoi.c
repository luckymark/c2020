#include <stdio.h>
int cnt=0;
void f(int n,char x,char y,char z){
    if(n<1) return;
    f(n-1,x,z,y);
    printf("%c->%c\n",x,z);
    cnt++;
    f(n-1,y,x,z);
}
int main() {
    int n;
    scanf("%d",&n);
    f(n,'A','B','C');
    printf("%d",cnt);
    return 0;
}