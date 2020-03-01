#ifndef P10_PUSHBOXES_BOXES_H
#define P10_PUSHBOXES_BOXES_H

typedef struct {
    char **map;
    char filename[64];
    unsigned int moves, in_place;
    unsigned int height, width;
    unsigned int x, y;
    unsigned int boxes, targets;
    unsigned int *boxes_x, *boxes_y;
    unsigned int *targets_x, *targets_y;
} Game;

void init_game(Game *game);
void print_map(Game *game);
void move(Game *game, int direction);
int move_box(Game *game, unsigned int box_x, unsigned int box_y, unsigned int direction);
void save_game(Game *game);
void quit_game(Game *game);

#endif //P10_PUSHBOXES_BOXES_H
