#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_str() {
    char *str = (char*)malloc(sizeof(char));
    int len = 0;
    char ch = 0;

    while ((ch = getchar()) != '\n') {
        *(str+len) = ch;
        len++;
        str = realloc(str, (len + 1) * sizeof(char));
    }
    *(str+len) = 0;

    return str;
}

void encrypt(char *str) {
    // Affine_cipher and ROT13
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 65 && str[i] <= 90) {
            // upper
            int ch = str[i] - 65;
            ch = (5 * ch + 8) % 26;
            ch = (ch + 13) % 26;
            str[i] = ch + 65;
        } else if (str[i] >= 97 && str[i] <= 122) {
            // lower
            int ch = str[i] - 97;
            ch = (5 * ch + 8) % 26;
            ch = (ch + 13) % 26;
            str[i] = ch + 97;
        }
    }
}

void decrypt(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 65 && str[i] <= 90) {
            // upper
            int ch = str[i] - 65;
            ch = (ch + 13) % 26;
            ch = (21 * (ch - 8)) % 26;
            str[i] = ch + 65;
        } else if (str[i] >= 97 && str[i] <= 122) {
            // lower
            int ch = str[i] - 97;
            ch = (ch + 13) % 26;
            ch = (21 * (ch - 8)) % 26;
            if (ch < 0) {
                ch += 26;
            }
            str[i] = ch + 97;
        }
    }
}
