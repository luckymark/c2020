#include<stdio.h>

int count=0;//这句话不知道能不能放到递归里面
int solve (char start,char end,char another,int num){
    if(num==0){
        return 0;
    }else{
        solve(start,another,end,num-1);
        printf("%c->%c\n",start,end); count++;
        solve(another,end,start,num-1);
    }return count;
}

int main(){
    int num=64;//圆盘个数
    printf("%d",solve('A','B','C',num));    
    return 0;
}