#include <stdio.h>
#include "boxes.h"

void print_map(char map[][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void move(char map[][WIDTH], int *x, int *y, int *boxes_x, int *boxes_y, const int *targets_x, const int *targets_y, int direction) {
    // direction:  0->Up  1->Down  2->Right  3->Left
    switch (direction) {
        case 0:
            if (map[*x - 1][*y] != '+') {
                if (map[*x - 1][*y] == '@' && !move_box(map, *x - 1, *y, boxes_x, boxes_y, 0)) {
                    break;
                }

                map[*x][*y] = ' ';
                (*x)--;
                map[*x][*y] = '#';
            }
            break;

        case 1:if (map[*x + 1][*y] != '+') {
                if (map[*x + 1][*y] == '@' && !move_box(map, *x + 1, *y, boxes_x, boxes_y, 1)) {
                    break;
                }

                map[*x][*y] = ' ';
                (*x)++;
                map[*x][*y] = '#';
            }
            break;

        case 2:
            if (map[*x][*y + 2] != '+') {
                if (map[*x][*y + 2] == '@' && !move_box(map, *x, *y + 2, boxes_x, boxes_y, 2)) {
                    break;
                }

                map[*x][*y] = ' ';
                (*y) += 2;
                map[*x][*y] = '#';
            }
            break;

        case 3:
            if (map[*x][*y - 2] != '+') {
                if (map[*x][*y - 2] == '@' && !move_box(map, *x, *y - 2, boxes_x, boxes_y, 3)) {
                    break;
                }

                map[*x][*y] = ' ';
                (*y) -= 2;
                map[*x][*y] = '#';
            }
            break;

        default:
            break;
    }

    for (int i = 0; i < BOXES; i++) {
        if (map[targets_x[i]][targets_y[i]] == ' ')
            map[targets_x[i]][targets_y[i]] = '*';
    }
}

int move_box(char map[][WIDTH], int box_x, int box_y, int *boxes_x, int *boxes_y, int direction) {
    int box;

    for (box = 0; box < BOXES; box++) {
        if (boxes_x[box] == box_x && boxes_y[box] == box_y)
            break;
    }

    switch (direction) {
        case 0:
            if (map[box_x - 1][box_y] != '+' && map[box_x - 1][box_y] != '@') {
                map[box_x][box_y] = ' ';
                box_x--;
                map[box_x][box_y] = '@';
            }
            break;

        case 1:
            if (map[box_x + 1][box_y] != '+' && map[box_x + 1][box_y] != '@') {
                map[box_x][box_y] = ' ';
                box_x++;
                map[box_x][box_y] = '@';
            }
            break;

        case 2:
            if (map[box_x][box_y + 2] != '+' && map[box_x][box_y + 2] != '@') {
                map[box_x][box_y] = ' ';
                box_y += 2;
                map[box_x][box_y] = '@';
            }
            break;

        case 3:
            if (map[box_x][box_y - 2] != '+' && map[box_x][box_y - 2] != '@') {
                map[box_x][box_y] = ' ';
                box_y -= 2;
                map[box_x][box_y] = '@';
            }
            break;

        default:
            break;
    }

    if (boxes_x[box] != box_x || boxes_y[box] != box_y) {
        boxes_x[box] = box_x;
        boxes_y[box] = box_y;
        return 1;
    } else {
        return 0;
    }
}
