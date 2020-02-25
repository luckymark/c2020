#include <stdio.h>

int main(){
    int num;
    scanf("%d", &num);
    if (num > 0){
        printf("是正数\n");
    }else if(num < 0){
        printf("是负数\n");
    }else{
        printf("是零\n");
    }
    
    if (num % 2 == 0)
    {
        printf("是偶数\n");
    }else{
        printf("是奇数\n");
    }
    return 0;
}
