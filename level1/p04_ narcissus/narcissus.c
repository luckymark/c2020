#include<stdio.h>
#include<stdbool.h>

bool isNarcissus(int n){
    int a=n/100;
    int b=(n/10)%10;
    int c=n%10;
    if(n==(a*a*a+b*b*b+c*c*c)) return true;  //pow(a,3); 头文件math.h
    else return false;
}



int main(){
    for(int i=100;i<1000;i++){
        if(isNarcissus(i)) printf("%d ",i);
    }
    printf("\n");

    return 0;
}