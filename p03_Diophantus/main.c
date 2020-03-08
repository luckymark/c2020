#include <stdio.h>

int main() {
    int ans;
    float x;
    for (int i = 10; i <200 ; ++i) {
        x = i;
        if ( (x/6 + x/12+x/7+5+x/2+4 ) == x )
            break;
    }
    ans = x-4;
    printf("The answer is %d",ans);
}
