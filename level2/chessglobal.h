#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
// player black
// ai white
#define C_NONE 0
#define C_BLACK 1
#define C_WHITE 2
#define C_BOUND 3
#define WIN 200000
#define LOSE -10000000

#define WHITE_LIVE_4 50000
#define BLACK_LIVE_4 -300000

#define WHITE_LIVE_3 400
#define BLACK_LIVE_3 -8000

#define WHITE_LIVE_2 20
#define BLACK_LIVE_2 -40

#define WHITE_LIVE_1 1
#define BLACK_LIVE_1 -2

//SLEEP
#define WHITE_SLEEP_4 400
#define BLACK_SLEEP_4 -200000

#define WHITE_SLEEP_3 20
#define BLACK_SLEEP_3 -40

#define WHITE_SLEEP_2 1
#define BLACK_SLEEP_2 -2


const int CHESS_HEIGHT                     = 17;
const int CHESS_LENGTH                     = 17;
const int depth_MAX                        = 6;
const int MAX_CHOICE                       = 10;
const int STEPS                            = 3;/*局部搜索中沿非空点走的深度（步数）*/


const int PAINT_X                          = 7;
const int PAINT_Y                          = 7;
const int CHESS_LINE_PIECE                 = 15;
const int CHESS_PIECE_LINE_DISTANCE        = 5;
const int CHESS_PIECE_HEIGHT_DISTANCE      = 2;
const int CHESS_PIECE_CHECK_POS_DIS_LINE   = 3;
const int CHESS_PIECE_CHECK_POS_DIS_HEIGHT = 2;

int chess_6_type[4][4][4][4][4][4];
int dir[8][2] = {{1,0},{0,1},{1,1},{1,-1},{-1,0},{0,-1},
{-1,1},{-1,-1}};
int board[CHESS_HEIGHT][CHESS_LENGTH];

struct boardStatus{
    int status,score;
};

struct Points{
    int x,y;
}AIStep;

struct decision{
    Points pos[MAX_CHOICE];
    int score[MAX_CHOICE];
};

void AI(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],HANDLE handleOut);
void init_Chess_6_Type();
int alphaBetaSearch(int (&board)[CHESS_HEIGHT][CHESS_LENGTH], int depth, int alpha, int beta);
decision findPoints(int (&board)[CHESS_HEIGHT][CHESS_LENGTH]);
bool judgePoints(int x,int y);
boardStatus evaluateBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH]);
void copychess(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&sameBoard)[CHESS_HEIGHT][CHESS_LENGTH]);
void revBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&reverseBoard)[CHESS_HEIGHT][CHESS_LENGTH]);
bool judgeChessBoardStatus(int (&board)[CHESS_HEIGHT][CHESS_LENGTH]);

void player(HANDLE handleIn,HANDLE handleOut,int (&board)[CHESS_HEIGHT][CHESS_LENGTH]);
void draw_Chess_Line(HANDLE handleOut,DWORD a);
COORD getMouse(HANDLE handleIn);
COORD getChessPosition(COORD pos_Mouse);
void load_UI_Tips(HANDLE handleOut);
void writeChessPiece(int x,int y,HANDLE handleOut,char* s);
