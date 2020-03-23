#include <stdio.h>

void move(int n, int start, int end);

//将n个从start移动到end
void move(int n, int start, int end) {
    if (n == 1) {
        printf("%d --> %d\n", start, end);

    } else {
        move(n - 1, start, 6 - start - end);
        printf("%d --> %d\n", start, end);
        move(n - 1, 6 - start - end, end);
    }
}

int main(void) {
    puts("1,2,3 represent A,B,C respectively. ");
    int n = 0;
    puts("Please input the quantity of plate.(Origin story is 64)");
    scanf("%d",&n);
    puts("---------");
    move(n,1,2);
    return 0;
}