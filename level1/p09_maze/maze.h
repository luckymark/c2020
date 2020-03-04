#ifndef P09_MAZE_MAZE_H
#define P09_MAZE_MAZE_H

typedef struct {
    char **maze;
    char filename[64];
    unsigned int height, width;
    unsigned int x, y;
    unsigned int target_x, target_y;
} Game;

void init_game(Game *game);
void print_maze(Game *game);
void move(Game *game, int direction);
void quit_game(Game *game);

#endif //P09_MAZE_MAZE_H
