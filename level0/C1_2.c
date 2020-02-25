#include <stdio.h>

int main(){
    int num;
    scanf("%d", &num);
    //是否是13的倍数
    if(num < 13){
        printf("No\n");
    }else if(num % 13 == 0){
        printf("Yes\n");
    }
    return 0;
}
