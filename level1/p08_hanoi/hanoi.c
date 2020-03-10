#include <stdio.h>

void move(int a,int p1, int p2){
    if(a == 0) return;
    int p3;
    if(p1 + p2 == 3){   //p1和p2是1或2
        p3 = 3;
    }else if(p1 + p2 == 5){ //p1和p2是2或3
        p3 = 1;
    }else{
        p3 = 2;
    }
    move(a-1,p1,p3);
    printf("%d:%d-->%d\n",a,p1,p2);
    move(a-1,p3,p2);
}

int main(){
    int n;
    printf("input n:\n");
    scanf("%d",&n);
    move(n,1,3);
    printf("A:p1-->p2   move A from p1 to p2\n");
}
