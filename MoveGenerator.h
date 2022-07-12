//
// Created by Azuolas on 7/6/2022.
//

#ifndef CHESS_ENGINE_MOVEGENERATOR_H
#define CHESS_ENGINE_MOVEGENERATOR_H

#include <iostream>
#include <vector>
#include <functional>
#include "ChessBoard.h"
#include "Position.h"
#include "BoardUtility.h"

struct Move
{
    Move()
    {

    }

    Move(int fromX, int fromY, int toX, int toY)
    {
        startingX = fromX;
        startingY = fromY;
        destinationX = toX;
        destinationY = toY;
    }

    int startingX, startingY;
    int destinationX, destinationY;
    std::function<void()> additionalAction = nullptr;
};

class MoveGenerator
{
    ChessEngine::Position* position;
    //ChessEngine::ChessBoard* board;

    bool IsSameColor(int startingX, int startingY, int destinationX, int destinationY);
    bool IsInBounds(int x, int y);

public:
    MoveGenerator(ChessEngine::Position* position)
    {
        this-> position = position;
        //board = position.board;
    }

    std::vector<Move> GenerateStraightMoves(int startingX, int startingY);
    std::vector<Move> GenerateDiagonalMoves(int startingX, int startingY);
    std::vector<Move> GenerateKnightMoves(int startingX, int startingY);
    std::vector<Move> GenerateKingMoves(int startingX, int startingY);
    std::vector<Move> GenerateCastlingMoves(int startingX, int startingY);
    std::vector<Move> GeneratePawnMoves(int startingX, int startingY);

    std::vector<Move> CombineVectors(std::vector<Move> a, std::vector<Move> b);
    bool doesContainMove(std::vector<Move> generatedMoves, int x, int y, Move* correctMove);
};


#endif //CHESS_ENGINE_MOVEGENERATOR_H
