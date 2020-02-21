#include <stdio.h>

int main(void) {
    int f_age, s_age;

    for (f_age = 4; f_age < 120; f_age++) {
        if (f_age % 7 == 0 && f_age %12 == 0) {
            s_age = f_age / 2;
            if (f_age / 6 + f_age / 12 + f_age / 7 + 5 + s_age + 4 == f_age) {
                break;
            }
        }
    }

    printf("儿子死时丢番图的年龄是%d", f_age - 4);

    return 0;
}
