//
// Created by Azuolas on 7/6/2022.
//

#ifndef CHESS_ENGINE_MOVEGENERATOR_H
#define CHESS_ENGINE_MOVEGENERATOR_H

#include <iostream>
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

    bool IsSameColor(int startingX, int startingY, int destinationX, int destinationY);
    bool IsInBounds(int x, int y);

public:
    MoveGenerator(ChessEngine::ChessBoard board)
    {
        this->board = board;
    }
    std::vector<Move> GenerateStraightMoves(int startingX, int startingY);
    std::vector<Move> GenerateDiagonalMoves(int startingX, int startingY);
    std::vector<Move> GenerateKnightMoves(int startingX, int startingY);
    std::vector<Move> GenerateKingMoves(int startingX, int startingY);
    std::vector<Move> GeneratePawnMoves(int startingX, int startingY);
};


#endif //CHESS_ENGINE_MOVEGENERATOR_H
