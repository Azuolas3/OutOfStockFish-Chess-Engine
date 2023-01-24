//
// Created by Azuolas on 1/23/2023.
//

#ifndef CHESS_ENGINE_EVALUATOR_H
#define CHESS_ENGINE_EVALUATOR_H

#include "Position.h"
#include "PieceSquareTables.h"

namespace ChessEngine
{
    class Evaluator
    {
        std::map<PieceType, int> pieceValueMap =
        {
                {PAWN, 100},
                {BISHOP, 300},
                {KNIGHT, 300},
                {ROOK, 500},
                {QUEEN, 900},
                {KING, 0} // dont need king value to influence material count
        };

        ChessBoard* currentBoard;

        int GetMaterialCount(Color side);
        int EvaluatePieceSquareTables(Color side);

    public:
        explicit Evaluator(Position* position)
        {
            currentPosition = position;
            currentBoard = position->board;
        }

        float EvaluatePosition();

        Position* currentPosition;
    };

} // ChessEngine

#endif //CHESS_ENGINE_EVALUATOR_H
