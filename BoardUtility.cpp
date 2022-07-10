//
// Created by Azuolas on 7/10/2022.
//

#include "BoardUtility.h"

namespace ChessEngine
{
    bool IsKingsideEmpty(Color color, Piece board[8][8])
    {
        int kingRank = (color == WHITE) ? 0 : 7;

        if(board[5][kingRank] == EMPTY && board[6][kingRank] == EMPTY)
            return true;
        else
            return false;
    }

    bool IsQueensideEmpty(Color color, Piece board[8][8])
    {
        int kingRank = (color == WHITE) ? 0 : 7;

        if(board[1][kingRank] == EMPTY && board[2][kingRank] == EMPTY && board[3][kingRank] == EMPTY)
            return true;
        else
            return false;
    }
}
