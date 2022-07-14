//
// Created by Azuolas on 7/10/2022.
//

#include "BoardUtility.h"

namespace ChessEngine
{
    bool IsInBounds(int x, int y)
    {
        if ( x >= 0 && x <= 7 && y >= 0 && y <= 7)
            return true;
        else
            return false;
    }

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

    bool isAbsolutelyPinned(int x, int y, Piece board[8][8])
    {

    }

    Piece FindFirstPieceInDirection(int startingX, int startingY, Direction dir, Piece board[8][8])
    {
        int offsetX, offsetY;
        switch(dir)
        {
            case NORTHWEST:
                offsetX = -1;
                offsetY = 1;
                break;

            case NORTH:
                offsetX = 0;
                offsetY = 1;
                break;

            case NORTHEAST:
                offsetX = 1;
                offsetY = 1;
                break;

            case WEST:
                offsetX = -1;
                offsetY = 0;
                break;

            case EAST:
                offsetX = 1;
                offsetY = 0;
                break;

            case SOUTHWEST:
                offsetX = -1;
                offsetY = -1;
                break;

            case SOUTH:
                offsetX = 0;
                offsetY = -1;
                break;

            case SOUTHEAST:
                offsetX = 1;
                offsetY = -1;
                break;

        }

        for(int x = startingX + offsetX, y = startingY + offsetY;; x += offsetX, y += offsetY)
        {
            if(IsInBounds(x, y))
            {
                if(board[x][y] != EMPTY)
                    return board[x][y];
            }
            else
            {
                return EMPTY;
            }
        }
    }
}
