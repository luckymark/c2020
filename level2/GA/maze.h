#ifndef GA_MAZE_H
#define GA_MAZE_H

#define HEIGHT 5
#define WIDTH 5

typedef struct {
    char maze[HEIGHT][WIDTH + 1];
    unsigned int x, y;
    unsigned int target_x, target_y;
} Game;

void init_game(Game *game);
void print_maze(const Game *game);
int move(Game *game, int direction);

#endif //GA_MAZE_H
