#include <stdio.h>
#define MAXN 1000
int main() {
    int book[MAXN + 1] = {0};
    for (int i = 2; i <= MAXN; i++) {
        if (!book[i]) printf("%d\n", i);
        for (int j = i; j <= MAXN; j += i) book[j] = 1;
    }
    return 0;
}
