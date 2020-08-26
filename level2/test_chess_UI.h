void draw_Chess_Line(HANDLE handleOut,DWORD a)
{
    COORD pos_paint;
    pos_paint.X = PAINT_Y;
    pos_paint.Y = PAINT_X;
    FillConsoleOutputCharacter(handleOut,'-',2 * CHESS_LINE_PIECE + 3 * (CHESS_LINE_PIECE - 1),pos_paint,&a);
    for(int i = 1;i < 15;i++)
    {
        COORD pos_paint_now_1 = pos_paint;
        COORD pos_paint_now_2 = pos_paint;
        pos_paint_now_1.Y++;
        pos_paint_now_2.Y+=2;
        pos_paint.Y +=3;
        for(int j = 1;j <= 15;j++)
        {
            WriteConsoleOutputCharacter(handleOut,"｜",2,pos_paint_now_1,&a);
            WriteConsoleOutputCharacter(handleOut,"｜",2,pos_paint_now_2,&a);
            pos_paint_now_1.X += CHESS_PIECE_LINE_DISTANCE;
            pos_paint_now_2.X += CHESS_PIECE_LINE_DISTANCE;
        }
        FillConsoleOutputCharacter(handleOut,'-',2 * CHESS_LINE_PIECE + 3 * (CHESS_LINE_PIECE - 1),pos_paint,&a);
    }
}

 COORD getMouse(HANDLE handleIn)
 {
     DWORD a;
     INPUT_RECORD mouseRecord;
     while(1)
     {
         ReadConsoleInput(handleIn, &mouseRecord, 1,&a);
         if(mouseRecord.EventType == MOUSE_EVENT)
         {
            //if(mouseRecord.Event.MouseEvent.dwEventFlags  == MOUSE_MOVED  )
			if(mouseRecord.Event.MouseEvent.dwButtonState  == FROM_LEFT_1ST_BUTTON_PRESSED)
             {
                 COORD pos = mouseRecord.Event.MouseEvent.dwMousePosition;
                 return pos;
             }
         }
     }
 }

COORD getChessPosition(COORD pos_Mouse)
{
	pos_Mouse.X -= PAINT_Y;
	pos_Mouse.Y -= PAINT_X;
    COORD pos_Chess;
    int dis_height = (2 * CHESS_PIECE_CHECK_POS_DIS_HEIGHT - 1);
    int x = pos_Mouse.Y;
    int y = pos_Mouse.X;
    for(int i = 1;i <= CHESS_HEIGHT;i++)
    {
        for(int j = 1;j <= CHESS_LENGTH;j++)
        {
            if((i - 1) * dis_height - CHESS_PIECE_CHECK_POS_DIS_HEIGHT <= x 
			&& (i - 1) * dis_height + CHESS_PIECE_CHECK_POS_DIS_HEIGHT >= x
            && (j - 1) * CHESS_PIECE_LINE_DISTANCE  - CHESS_PIECE_CHECK_POS_DIS_LINE <= y 
			&& (j - 1) * CHESS_PIECE_LINE_DISTANCE + CHESS_PIECE_CHECK_POS_DIS_LINE >= y)
            {
                pos_Chess.X = i;
                pos_Chess.Y = j;
                return pos_Chess;
            }
        }
    }
}

void load_UI_Tips(HANDLE handleOut)
{
    DWORD a;
    COORD pos_Text;
    pos_Text.X = PAINT_Y;
    pos_Text.Y = PAINT_X - 3;
    WriteConsoleOutputCharacter(handleOut,"单击鼠标左键落子",16,pos_Text,&a);
}

void writeChessPiece(int x,int y,HANDLE handleOut,char* s)
{
    COORD pos_paint;
    DWORD a;
    int dis_height = (2 * CHESS_PIECE_CHECK_POS_DIS_HEIGHT - 1);
    pos_paint.Y = (x - 1) * dis_height + PAINT_X;
    pos_paint.X = (y - 1) * (CHESS_PIECE_LINE_DISTANCE) + PAINT_Y;
    WriteConsoleOutputCharacter(handleOut,s,2,pos_paint,&a);
}

void player(HANDLE handleIn,HANDLE handleOut,int (&board)[CHESS_HEIGHT][CHESS_LENGTH])
{
    COORD pos_Paint;
    COORD pos_Chess;
    while(1)
    {
    	pos_Paint = getMouse(handleIn);
    	pos_Chess = getChessPosition(pos_Paint);
    	if(board[pos_Chess.X][pos_Chess.Y] == C_NONE)
    	{
    		break;
		}
	}
    writeChessPiece(pos_Chess.X,pos_Chess.Y,handleOut,"●");
    board[pos_Chess.X][pos_Chess.Y] = C_BLACK;
}
