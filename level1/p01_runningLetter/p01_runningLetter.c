#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // #include <unistd.h>

#define WORD "Look_at_Me"
#define SECOND 1000
#define WIDTH 80
#define FPS 30

const int TERMINAL = WIDTH - sizeof(WORD) / sizeof(char) + 1;
int position = 0, delta = 1;

void step() {
	position += delta;
	if (position < 0 || position > TERMINAL) {
		position -= delta;
		delta *= -1;
		position += delta;
	}
}

void render() {
	system("cls");
	for (int p = 0; p < position; p++)
		printf(" ");
	printf(WORD);
	Sleep(SECOND / FPS); // usleep(SECOND / FPS * 1000)
}

int main() {
	char command[100];
	sprintf(command, "mode concols=%d lines=1", WIDTH);
	system(command);
	for (;;) {
		render();
		step();
	}
	return 0;
}
