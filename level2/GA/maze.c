#include <stdio.h>
#include <string.h>
#include "maze.h"

const char map[][16] = {
        "11111",
        "15001",
        "10101",
        "10101",
        "11181"
};

void init_game(Game *game) {
    for (int i = 0; i < HEIGHT; i++) {
        strcpy(game->maze[i], map[i]);
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch (game->maze[i][j]) {
                case '5':
                    game->x = i;
                    game->y = j;
                    break;
                case '8':
                    game->target_x = i;
                    game->target_y = j;
                    break;
                default:
                    break;
            }
        }
    }
}

void print_maze(const Game *game) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch (game->maze[i][j]) {
                case '0':
                    printf("  ");
                    break;
                case '1':
                    printf("+ ");
                    break;
                case '5':
                    printf("# ");
                    break;
                case '8':
                    printf("* ");
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
}

int move(Game *game, int direction) {
    if (game->x == game->target_x && game->y == game->target_y) {
        return 1;
    }
    // direction:  0->Up  1->Down  2->Right  3->Left
    switch (direction) {
        case 0:
            if (game->maze[(game->x)-1][game->y] != '1') {
                game->maze[game->x][game->y] = '0';
                (game->x)--;
                game->maze[game->x][game->y] = '5';
            }
            break;

        case 1:if (game->maze[(game->x)+1][game->y] != '1') {
                game->maze[game->x][game->y] = '0';
                (game->x)++;
                game->maze[game->x][game->y] = '5';
            }
            break;

        case 2:
            if (game->maze[game->x][(game->y)+1] != '1') {
                game->maze[game->x][game->y] = '0';
                (game->y) += 1;
                game->maze[game->x][game->y] = '5';
            }
            break;

        case 3:
            if (game->maze[game->x][(game->y)-1] != '1') {
                game->maze[game->x][game->y] = '0';
                (game->y) -= 1;
                game->maze[game->x][game->y] = '5';
            }
            break;

        default:
            break;
    }
    return 0;
}
