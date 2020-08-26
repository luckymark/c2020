void copychess(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&sameBoard)[CHESS_HEIGHT][CHESS_LENGTH])
{
    for(int i = 0;i < CHESS_HEIGHT;i++)
    {
        for(int j = 0;j < CHESS_LENGTH;j++)
        {
            sameBoard[i][j] = board[i][j];
        }
    }
}

void revBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&reverseBoard)[CHESS_HEIGHT][CHESS_LENGTH])
{
    for(int i = 0;i < CHESS_HEIGHT;i++)
    {
        for(int j = 0;j < CHESS_LENGTH;j++)
        {
            if(board[i][j] == C_BLACK)
            {
                reverseBoard[i][j] = C_WHITE;
            }
            else if(board[i][j] == C_WHITE)
            {
                reverseBoard[i][j] = C_BLACK;
            }
            else
            {
                reverseBoard[i][j] = board[i][j];
            }
        }
    }
}

boardStatus evaluateBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])
{
    boardStatus evalutation;
    int score = 0, status = 0;

    for(int k = 0;k < 4;k++)
    {
        for(int i = 0;i < CHESS_HEIGHT;i++)
        {
            for(int j = 0;j < CHESS_LENGTH;j++)
            {
                int max_x = i + dir[k][0] * 5,max_y = j + dir[k][1] * 5, pre = score;
                if(max_x < 0 || max_x >= CHESS_HEIGHT || max_y < 0 || max_y >= CHESS_LENGTH) continue;

                score += chess_6_type[board[i][j]][board[i + dir[k][0]][j + dir[k][1]]][board[i + dir[k][0] * 2][j + dir[k][1] * 2]][board[i + dir[k][0] * 3][j + dir[k][1] * 3]][board[i + dir[k][0] * 4][j + dir[k][1] * 4]][board[i + dir[k][0] * 5][j + dir[k][1] * 5]];
                if(score - pre == WIN)
                {
                    status = 1;
                }
                else if(score - pre == LOSE)
                {
                    status = 2;
                }
            }
        }
    }
    evalutation.score = score;
    evalutation.status = status;
    return evalutation;
}


bool judgePoints(int x,int y)
{
    if(x <= 0 || x >= CHESS_HEIGHT - 1 || y <= 0 || y >= CHESS_LENGTH - 1)
    {
        return false;
    }
    return true;
}

decision findPoints(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])
{
    bool placepiece[CHESS_HEIGHT][CHESS_LENGTH];
    decision P;
    memset(placepiece,0,sizeof(placepiece));
    for(int i = 1;i < CHESS_HEIGHT - 1;i++)
    {
        for(int j = 1;j < CHESS_LENGTH - 1;j++)
        {
            if(board[i][j] == C_NONE || board[i][j] == C_BOUND) continue;
            for(int k = 1;k <= STEPS;k++)
            {
                for(int d = 0;d < 8;d++)
                {
                    if(judgePoints(i + dir[d][0] * k,j + dir[d][1] * k) 
                    && board[i + dir[d][0] * k][j + dir[d][1] * k] == 0)
                    {
                        placepiece[i + dir[d][0] * k][j + dir[d][1] * k] = true;
                    }
                }
            }
        }
    }
    int valueBoard[CHESS_HEIGHT][CHESS_LENGTH];
    for(int i = 1;i < CHESS_HEIGHT - 1;i++)
    {
        for(int j = 1;j < CHESS_LENGTH - 1;j++)
        {
            if(placepiece[i][j])
            {
                board[i][j] = C_WHITE;
                valueBoard[i][j] = evaluateBoard(board).score;
                board[i][j] = C_NONE;
            }
            else
            {
                valueBoard[i][j] = -INT_MAX;
            }
            
        }
    }
    for(int k = 0;k < MAX_CHOICE;k++)
    {
        int maxvalue = -INT_MAX;
        bool flag = false;
        for(int i = 1;i < CHESS_HEIGHT - 1;i++)
        {
            for(int j = 1;j < CHESS_LENGTH - 1;j++)
            {
                if(maxvalue < valueBoard[i][j])
                {
                    maxvalue = valueBoard[i][j];
                    P.pos[k].x = i;
                    P.pos[k].y = j;
                    P.score[k] = maxvalue;
                    flag = true;
                }
            }
        }
        if(flag)
        {
            valueBoard[P.pos[k].x][P.pos[k].y] = -INT_MAX;
        }
    }
    return P;
}

int alphaBetaSearch(int (&board)[CHESS_HEIGHT][CHESS_LENGTH], int depth, int alpha, int beta)
{
    boardStatus result = evaluateBoard(board);
    if(depth == 0 || result.status != 0)
    {
        if(depth == 0)
        {
            decision P;
            P = findPoints(board);
            return P.score[0];
        }
        else return result.score;
    }
    else if(depth % 2 == 0)
    {
        int sameBoard[CHESS_HEIGHT][CHESS_LENGTH];
        copychess(board,sameBoard);
        decision P = findPoints(sameBoard);

        for(int i = 0;i < MAX_CHOICE;i++)
        {
            sameBoard[P.pos[i].x][P.pos[i].y] = C_WHITE;
            int score = alphaBetaSearch(sameBoard, depth - 1,alpha,beta);
            sameBoard[P.pos[i].x][P.pos[i].y] = C_NONE;
            if(score > alpha)
            {
                alpha = score;
                if(depth == depth_MAX)
                {
                    AIStep = P.pos[i];
                }
            }
            if(alpha >= beta) break;
        }
        return alpha;
    }
    else
    {
        int reverseBoard[CHESS_HEIGHT][CHESS_LENGTH];
        revBoard(board,reverseBoard);
        decision P = findPoints(reverseBoard);

        int sameBoard[CHESS_HEIGHT][CHESS_LENGTH];
        copychess(board,sameBoard);

        for(int i = 0;i < MAX_CHOICE;i++)
        {
            sameBoard[P.pos[i].x][P.pos[i].y] = C_BLACK;
            int score = alphaBetaSearch(sameBoard,depth - 1,alpha,beta);
            sameBoard[P.pos[i].x][P.pos[i].y] = C_NONE;
            if(score < beta)
            {
                beta = score;
            }
            if(alpha >= beta) break;
        }
        return beta;
    }
}

bool judgeChessBoardStatus(int (&board)[CHESS_HEIGHT][CHESS_LENGTH])
{
    boardStatus chess_Board = evaluateBoard(board);
    if(chess_Board.status == 0)
    {
        return false;
    }
    if(chess_Board.status == 1)
    {
        printf("You Lose");
        
    }
    else if(chess_Board.status == 2)
    {
        printf("You win");
    }
    return true;
    system("pause");
}

void AI(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],HANDLE handleOut)
{
    alphaBetaSearch(board,depth_MAX,-INT_MAX,INT_MAX);
    writeChessPiece(AIStep.x,AIStep.y,handleOut,"○");
    board[AIStep.x][AIStep.y] = C_WHITE;
}
