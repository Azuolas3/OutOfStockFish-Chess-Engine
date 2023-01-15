//
// Created by Azuolas on 7/10/2022.
//

#include "BoardUtility.h"

using namespace ChessEngine;

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
        return false;
    }

    Piece FindFirstPieceInDirection(int startingX, int startingY, Direction dir, Piece board[8][8])
    {
        for(int x = startingX + xDirOffset[dir], y = startingY + yDirOffset[dir];; x += xDirOffset[dir], y += yDirOffset[dir])
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

    void CastRayToSquare(bool table[8][8], Square startingPos, Square endingPos)
    {
        int xDistance = startingPos.x - endingPos.x;
        int yDistance = startingPos.y - endingPos.y;

        int xOffset;
        int yOffset;

        if(xDistance > 0)
            xOffset = 1;
        else if(xDistance == 0)
            xOffset = 0;
        else
            xOffset = -1;

        if(yDistance > 0)
            yOffset = 1;
        else if(yDistance == 0)
            yOffset = 0;
        else
            yOffset = -1;


        int x = endingPos.x + xOffset;
        int y = endingPos.y + yOffset;

        while(x != startingPos.x || y != startingPos.y)
        {
            table[x][y] = true;

            x += xOffset;
            y += yOffset;
        }
    }

    void CastRayInDirection(bool (*table)[8], Square startingPos, Square direction)
    {
        for(int x = startingPos.x, y = startingPos.y;; x += direction.x, y += direction.y) // x y doesnt change, infinite loop
        {
            if(IsInBounds(x, y))
            {
                table[x][y] = true;
            }
            else
                break;
        }
    }

    Square NormalizeVector(Square vector)
    {
        Square normalizedSquare{};

        if(vector.x == 0)
            normalizedSquare.x = 0;
        else if (vector.x > 0)
            normalizedSquare.x = 1;
        else
            normalizedSquare.x = -1;

        if(vector.y == 0)
            normalizedSquare.y = 0;
        else if (vector.y > 0)
            normalizedSquare.y = 1;
        else
            normalizedSquare.y = -1;

        return normalizedSquare;
    }

}

