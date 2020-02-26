#include <stdio.h>
#include <string.h>

int N = 5;//输入多少个数
int a[10];
int main(){
    memset(a,0,sizeof(a));
    for (int i = 0; i < N; ++i) {
        int num;
        scanf("%d", &num);
        a[num]++;
    }
    for (int i = 0; i < 10; ++i) {
        while(a[i]--){
            printf("%d ", i);
        }
    }
}
