//
// Created by pointkab on 2020/3/7.
//

#ifndef P09_MAZE_GAME_H
#define P09_MAZE_GAME_H
#include <windows.h>
typedef struct _Player {
    int GameStatus;
    COORD coord;
} player;
void ShowMap();
void Start ();
int IsWin();
void Move(int, int);
void SetPosition(COORD pos);
#endif //P09_MAZE_GAME_H
