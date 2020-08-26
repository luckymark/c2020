#include"chessglobal.h"
#include"chessAI.h"
#include"test_chess_UI.h"
#include"init_chess.h"

int main()
{
    HANDLE handleIn,handleOut;
    DWORD a;
    handleIn = GetStdHandle(STD_INPUT_HANDLE);
    handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    draw_Chess_Line(handleOut, a);
    memset(board,0,sizeof(board));
    init_Chess_6_Type();
    load_UI_Tips(handleOut);
    while(1)
    {
        if(judgeChessBoardStatus(board))
        {
            break;
        }
        player(handleIn,handleOut,board);
        if(judgeChessBoardStatus(board))
        {
            break;
        }
        AI(board,handleOut);
    }
}
