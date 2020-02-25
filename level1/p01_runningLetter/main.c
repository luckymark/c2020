#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define WIDTH 80
#define SLEEP_TIME 25

int main(void) {
    while (1) {
        for (int i = 0; i < WIDTH; i++) {
            system("CLS");
            for (int j = 0; j < i; j++) {
                printf(" ");
            }
            printf("A");
            Sleep(SLEEP_TIME);
        }

        for (int i = WIDTH; i > 0; i--) {
            system("CLS");
            for (int j = 0; j < i; j++) {
                printf(" ");
            }
            printf("A");
            Sleep(SLEEP_TIME);
        }
    }
}
