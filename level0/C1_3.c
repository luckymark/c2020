#include <stdio.h>
#include <stdlib.h>

int main() {
    int year;
    int flag;
    scanf("%d", &year);
    if (year % 400 == 0) {
        flag = 1;
    } else if (year % 100 == 0) {
        flag = 0;
    } else if (year % 4 == 0) {
        flag = 1;
    }

    if (flag) {
        printf("YES");
    } else {
        printf("NO");
    }
    return 0;
}
