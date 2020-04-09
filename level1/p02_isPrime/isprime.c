#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int n;

inline int getNumber(){ 
    int temp;
    scanf("%d",&temp);
    if(temp<=0){ 
        printf("Invalid Input!\n");
        exit(-1);
    }
    return temp;
}
void checkNumber(int x);

int main(){ 
    n=getNumber();
    checkNumber(n);
    return 0;
}
void checkNumber(int x){ 
    if(1==x)goto no;
    if(2==x)goto yes;

    int top=(int)sqrt(x);
    register int i;
    for(i=2;i<top;++i){ 
        if((x%i)==0)goto no;
    }

yes:
    printf("Yes!\n");
    return;
no:
    printf("No!\n");
}
