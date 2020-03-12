//
// Created by pointkab on 2020/3/10.
//

#ifndef P10_PUSHBOXES_GAME_H
#define P10_PUSHBOXES_GAME_H
#include <stdlib.h>
#include <windows.h>
typedef struct _player{
    int Steps;
    int Target;
    COORD coord;
}player;
void ShowMap (const int*);
FILE * MapChoice (int);
void PrfMenu ();
void GetMapInfo (FILE*, const int *);
void Start (FILE*, int);
void Move (int *, int, int);
void Init(const int *);
void SetPosition (int, int);
int IsWin(int);
#endif //P10_PUSHBOXES_GAME_H
