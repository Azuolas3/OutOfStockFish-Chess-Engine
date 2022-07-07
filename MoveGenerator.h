//
// Created by Azuolas on 7/6/2022.
//

#ifndef CHESS_ENGINE_MOVEGENERATOR_H
#define CHESS_ENGINE_MOVEGENERATOR_H

#include <vector>
#include "ChessBoard.h"

struct Move
{
    Move(int fromX, int fromY, int toX, int toY)
    {
        startingX = fromX;
        startingY = fromY;
        destinationX = toX;
        destinationY = toY;
    }

    int startingX, startingY;
    int destinationX, destinationY;
};

class MoveGenerator
{
    ChessEngine::ChessBoard board;

public:
    std::vector<Move> GenerateStraightMoves(int startingX, int startingY);
    std::vector<Move> GenerateDiagonalMoves(int startingX, int startingY);
};


#endif //CHESS_ENGINE_MOVEGENERATOR_H
