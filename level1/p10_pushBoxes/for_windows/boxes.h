#ifndef P10_PUSHBOXES_BOXES_H
#define P10_PUSHBOXES_BOXES_H

#define HEIGHT 15
#define WIDTH 29
#define BOXES 2

void print_map(char map[][WIDTH]);
void move(char map[][WIDTH], int *x, int *y, int *boxes_x, int *boxes_y, const int *targets_x, const int *targets_y, int direction);
int move_box(char map[][WIDTH], int box_x, int box_y, int *boxes_x, int *boxes_y, int direction);

#endif //P10_PUSHBOXES_BOXES_H
