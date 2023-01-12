//
// Created by Azuolas on 1/12/2023.
//

#include "Move.h"

Move InverseMove(const Move& move)
{
    return Move(move.destinationX, move.destinationY, move.startingX, move.startingY);
}