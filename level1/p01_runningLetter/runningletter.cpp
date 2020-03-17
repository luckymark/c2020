 #include <stdio.h>
#include <stdlib.h>
#include <windows.h>
const int wide = 10;
int main() {
	int i = 0;
	while (1) {
		for (i; i <= wide; i++) {
			for (int j = 0; j <= i; j++) printf(" ");
			printf("Hello, World!");
			system("cls");
			//Sleep(2000);
		}
		i -= 1;
		for (i; i >= 0; i--) {
			for (int j = 0; j <= i; j++) printf(" ");
			printf("Hello, World!");
			system("cls");
			//Sleep(2000);
		}
	}
	return 0;
}
