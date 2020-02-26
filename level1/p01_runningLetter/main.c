#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define WIDTH 80
#define SLEEP_TIME 25

int main(void) {
    int i = 0; 
    int change = 1;
    while (1) {
        system("CLS");
        for (int j = 0; j < i; j++) {
            printf(" ");
        }
        printf("A");
        Sleep(SLEEP_TIME);

        i += change;
        
        if (i == WIDTH - 1) {
            change = -1;
        } else if (i == 0) {
            change = 1;
        }
    }

    return 0;
}
