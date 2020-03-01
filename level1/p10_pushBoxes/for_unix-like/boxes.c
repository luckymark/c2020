#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boxes.h"

void init_game(Game *game) {
    char buf[255];
    FILE *fp = fopen(game->filename, "r");

    if (fp) {
        game->boxes = 0;
        game->boxes_x = NULL;
        game->boxes_y = NULL;
        game->targets = 0;
        game->targets_x = NULL;
        game->targets_y = NULL;
        game->height = 0;
        game->moves = 0;
        game->map = NULL;
        while (fgets(buf, 255, fp) && buf[0] != '\n') {
            game->map = (char**)realloc(game->map, sizeof(char*) * ((game->height) + 1));
            game->map[game->height] = (char*)malloc(sizeof(char) * (strlen(buf) + 1));

            strcpy(game->map[game->height], buf);

            (game->height)++;
        }
        game->width = strlen(game->map[0]);

        for (int i = 0; i < game->height; i++) {
            for (int j = 0; j < game->width; j++) {
                switch (game->map[i][j]) {
                    case '#':
                        game->x = i;
                        game->y = j;
                        break;

                    case '@':
                        game->boxes_x = (unsigned int*)realloc(game->boxes_x, sizeof(unsigned int) * ((game->boxes) + 1));
                        game->boxes_y = (unsigned int*)realloc(game->boxes_y, sizeof(unsigned int) * ((game->boxes) + 1));
                        game->boxes_x[game->boxes] = i;
                        game->boxes_y[game->boxes] = j;
                        (game->boxes)++;
                        break;

                    case '*':
                        game->targets_x = (unsigned int*)realloc(game->targets_x, sizeof(unsigned int) * ((game->targets) + 1));
                        game->targets_y = (unsigned int*)realloc(game->targets_y, sizeof(unsigned int) * ((game->targets) + 1));
                        game->targets_x[game->targets] = i;
                        game->targets_y[game->targets] = j;
                        (game->targets)++;
                        break;

                    default:
                        break;
                }
            }
        }
        fclose(fp);
    }

}

void print_map(Game *game) {
    for (int i = 0; i < game->height; i++) {
        printf("%s", game->map[i]);
    }
}

void move(Game *game, int direction) {
    // direction:  0->Up  1->Down  2->Right  3->Left
    switch (direction) {
        case 0:
            if (game->map[(game->x) - 1][game->y] != '+') {
                if (game->map[(game->x) - 1][game->y] == '@' && !move_box(game, (game->x) - 1, game->y, 0)) {
                    break;
                }

                game->map[game->x][game->y] = ' ';
                (game->x)--;
                game->map[game->x][game->y] = '#';
                (game->moves)++;
            }
            break;

        case 1:if (game->map[(game->x) + 1][game->y] != '+') {
                if (game->map[(game->x) + 1][game->y] == '@' && !move_box(game, (game->x) + 1, game->y, 1)) {
                    break;
                }

                game->map[game->x][game->y] = ' ';
                (game->x)++;
                game->map[game->x][game->y] = '#';
                (game->moves)++;
            }
            break;

        case 2:
            if (game->map[game->x][(game->y) + 2] != '+') {
                if (game->map[game->x][(game->y) + 2] == '@' && !move_box(game, game->x, (game->y) + 2, 2)) {
                    break;
                }

                game->map[game->x][game->y] = ' ';
                (game->y) += 2;
                game->map[game->x][game->y] = '#';
                (game->moves)++;
            }
            break;

        case 3:
            if (game->map[game->x][(game->y) - 2] != '+') {
                if (game->map[game->x][(game->y) - 2] == '@' && !move_box(game, game->x, (game->y) - 2, 3)) {
                    break;
                }

                game->map[game->x][game->y] = ' ';
                (game->y) -= 2;
                game->map[game->x][game->y] = '#';
                (game->moves)++;
            }
            break;

        default:
            break;
    }

    for (int i = 0; i < game->targets; i++) {
        if (game->map[game->targets_x[i]][game->targets_y[i]] == ' ')
            game->map[game->targets_x[i]][game->targets_y[i]] = '*';
    }
}

int move_box(Game *game, unsigned int box_x, unsigned int box_y, unsigned int direction) {
    int box;

    for (box = 0; box < game->boxes; box++) {
        if (game->boxes_x[box] == box_x && game->boxes_y[box] == box_y)
            break;
    }

    switch (direction) {
        case 0:
            if (game->map[box_x - 1][box_y] != '+' && game->map[box_x - 1][box_y] != '@') {
                game->map[box_x][box_y] = ' ';
                box_x--;
                game->map[box_x][box_y] = '@';
            }
            break;

        case 1:
            if (game->map[box_x + 1][box_y] != '+' && game->map[box_x + 1][box_y] != '@') {
                game->map[box_x][box_y] = ' ';
                box_x++;
                game->map[box_x][box_y] = '@';
            }
            break;

        case 2:
            if (game->map[box_x][box_y + 2] != '+' && game->map[box_x][box_y + 2] != '@') {
                game->map[box_x][box_y] = ' ';
                box_y += 2;
                game->map[box_x][box_y] = '@';
            }
            break;

        case 3:
            if (game->map[box_x][box_y - 2] != '+' && game->map[box_x][box_y - 2] != '@') {
                game->map[box_x][box_y] = ' ';
                box_y -= 2;
                game->map[box_x][box_y] = '@';
            }
            break;

        default:
            break;
    }

    if (game->boxes_x[box] != box_x || game->boxes_y[box] != box_y) {
        game->boxes_x[box] = box_x;
        game->boxes_y[box] = box_y;
        return 1;
    } else {
        return 0;
    }
}

void save_game(Game *game) {
    FILE *fp = fopen(game->filename, "a");
    if (fp) {
        fprintf(fp, "%d moves\n", game->moves);
        fclose(fp);
    }
}

void quit_game(Game *game) {
    for (int i = 0; i < game->height; i++) {
        free(game->map[i]);
    }
    free(game->map);
    free(game->boxes_x);
    free(game->boxes_y);
    free(game->targets_x);
    free(game->targets_y);
}
