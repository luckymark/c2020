#include <stdio.h>

int main() {
    for(int i=100;i<1000;i++)
    {
        if(i==(i/100)^3+((i/10)%10)^3+(i%10)^3)
            printf("%d\n",i);
    }
    return 0;
}