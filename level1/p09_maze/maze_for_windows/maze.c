#include <stdio.h>
#include "maze.h"

void print_maze(char maze[][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

void move(char maze[][WIDTH], int *x, int *y, int direction) {
    // direction:  0->Up  1->Down  2->Right  3->Left
    switch (direction) {
        case 0:
            if (maze[*x-1][*y] != '+') {
                maze[*x][*y] = ' ';
                (*x)--;
                maze[*x][*y] = '#';
            }
            break;

        case 1:if (maze[*x+1][*y] != '+') {
                maze[*x][*y] = ' ';
                (*x)++;
                maze[*x][*y] = '#';
            }
            break;

        case 2:
            if (maze[*x][*y+2] != '+') {
                maze[*x][*y] = ' ';
                (*y) += 2;
                maze[*x][*y] = '#';
            }
            break;

        case 3:
            if (maze[*x][*y-2] != '+') {
                maze[*x][*y] = ' ';
                (*y) -= 2;
                maze[*x][*y] = '#';
            }
            break;

        default:
            break;
    }
}
