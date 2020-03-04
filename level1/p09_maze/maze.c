#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

void init_game(Game *game) {
    char buf[255];
    FILE *fp = fopen(game->filename, "r");
    game->maze = NULL;

    if (fp) {
        game->height = 0;
        while (fgets(buf, 255, fp) && buf[0] != '\n') {
            game->maze = (char**)realloc(game->maze, sizeof(char*) * ((game->height) + 1));
            game->maze[game->height] = (char*)malloc(sizeof(char) * (strlen(buf) + 1));

            strcpy(game->maze[game->height], buf);

            (game->height)++;
        }
        game->width = strlen(game->maze[0]);

        for (int i = 0; i < game->height; i++) {
            for (int j = 0; j < game->width; j++) {
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
        fclose(fp);
    }
}

void print_maze(Game *game) {
    for (int i = 0; i < game->height; i++) {
        for (int j = 0; j < game->width; j++) {
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

void move(Game *game, int direction) {
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
}

void quit_game(Game *game) {
    for (int i = 0; i < game->height; i++) {
        free(game->maze[i]);
    }
    free(game->maze);
}
