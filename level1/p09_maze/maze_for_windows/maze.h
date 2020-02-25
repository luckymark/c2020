#ifndef P09_MAZE_MAZE_H
#define P09_MAZE_MAZE_H

#define HEIGHT 15
#define WIDTH 29

void print_maze(char maze[][WIDTH]);
void move(char maze[][WIDTH], int *x, int *y, int direction);

#endif //P09_MAZE_MAZE_H
