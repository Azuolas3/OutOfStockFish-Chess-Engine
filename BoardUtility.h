//
// Created by Azuolas on 7/10/2022.
//

#ifndef CHESS_ENGINE_BOARDUTILITY_H
#define CHESS_ENGINE_BOARDUTILITY_H

#include "pieces.h"

namespace ChessEngine
{
    enum Direction
    {
        NORTHWEST = 1, NORTH, NORTHEAST, // the opposite of each direction is its negative value
        WEST, EAST = -4,
        SOUTHWEST, SOUTH, SOUTHEAST
    };

    bool IsInBounds(int x, int y);

    bool IsKingsideEmpty(Color color, Piece board[8][8]);
    bool IsQueensideEmpty(Color color, Piece board[8][8]);

    bool isAbsolutelyPinned(int x, int y, Piece board[8][8]);
    Piece FindFirstPieceInDirection(int startingX, int startingY, Direction dir, Piece board[8][8]);
}



#endif //CHESS_ENGINE_BOARDUTILITY_H
