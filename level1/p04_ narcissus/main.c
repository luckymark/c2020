#include <stdio.h>
#include <math.h>
#define START 100
#define END 999
int main() {
    int i;
    for (i = START; i < END; i++)
    {
        if((pow(i % 10, 3) + pow((i / 10) % 10, 3) + pow(i / 100, 3)) == i)
            printf("%d\t", i);
    }
    return 0;
}
