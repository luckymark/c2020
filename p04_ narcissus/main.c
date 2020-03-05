#include <stdio.h>

int pow3(int x){return x*x*x;}
int main() {
    int n1, n2, n3;
    for (int i = 100; i < 1000; ++i) {
        n1 = i % 10;
        n2 = (i / 10) % 10;
        n3 = i / 100;
        if (i == pow3(n1) + pow3(n2) + pow3(n3))
            printf("%d\n", i);
    }
    return 0;

}


