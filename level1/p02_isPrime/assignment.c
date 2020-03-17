#include <math.h>
#include <stdio.h>

void isPrime(int num);

void isPrime(int num) {
    int flag = 1;                     
    for (int i = 2; i <= sqrt(num); i+=flag) {
        if (num % i == 0) {
            printf("NO\n");
            return;
        }
        if(i==3&&flag==1)flag = 2;
    }
    printf("YES\n");
}

int main(void) {
    int num;
    scanf("%d", &num);
    isPrime(num);

    return 0;
}