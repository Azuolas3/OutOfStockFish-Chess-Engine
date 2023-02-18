//
// Created by Azuolas on 7/10/2022.
//

#ifndef CHESS_ENGINE_BOARDUTILITY_H
#define CHESS_ENGINE_BOARDUTILITY_H

#include "BoardRepresentation/pieces.h"
#include <cstdlib>

namespace ChessEngine
{
    struct Square // simple struct holding two numbers
    {
        int x;
        int y;

        Square() = default;

        Square(int posX, int posY)
        {
            x = posX;
            y = posY;
        }

        bool operator==(const Square& square) const
        {
            if(this->x == square.x && this->y == square.y)
                return true;
            else
                return false;
        }

        bool operator!=(const Square& square) const
        {
            if(this->x != square.x || this->y != square.y)
                return true;
            else
                return false;
        }
    };

    inline int xDirOffset[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    inline int yDirOffset[] = {1, 1, 1, 0, 0, -1, -1, -1};

    void CastRayToSquare(bool table[8][8], Square startingPos, Square endingPos); // sets each value from startingPos to endingPos as true
    void CastRayInDirection(bool table[8][8], Square startingPos, Square direction); // sets each value from startingPos to end of board in the given direction as true

    Square NormalizeVector(Square vector); // it doesn't quite normalize the vector, however changes it into a direction the code understands

    bool IsInBounds(int x, int y);

    bool IsKingsideEmpty(Color color, Piece board[8][8]);
    bool IsQueensideEmpty(Color color, Piece board[8][8]);
}



#endif //CHESS_ENGINE_BOARDUTILITY_H
