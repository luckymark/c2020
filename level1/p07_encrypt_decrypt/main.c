#include <stdio.h>
#include <stdlib.h>
#include "encrypt_decrypt.h"

int main(void) {
    while (1) {
        int mode = 0;

        printf("1) Encrypt\n");
        printf("2) Decrypt\n");
        printf("Enter the number to choose mode (q to quit): ");
        scanf("%d", &mode);
        getchar();

        if (mode == 1) {
            printf("\nEnter your plaintext:\n");
            char *str = get_str();
            encrypt(str);
            printf("\nYour ciphertext is:\n");
            printf("%s\n\n", str);
            free(str);
        } else if (mode == 2) {
            printf("\nEnter your ciphertext:\n");
            char *str = get_str();
            decrypt(str);
            printf("\nYour plaintext is:\n");
            printf("%s\n\n", str);
            free(str);
        } else if (mode == 'q'){
            printf("\nBye!\n\n");
            break;
        } else {
            printf("\nPlease enter 1 or 2!\n\n");
        }
    }

    return 0;
}
