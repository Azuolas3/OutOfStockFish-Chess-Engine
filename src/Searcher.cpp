//
// Created by Azuolas on 1/23/2023.
//

#include "Searcher.h"

namespace ChessEngine {
    int Searcher::Search(int depth)
    {
        if (depth == 0)
            return evaluator->EvaluatePosition();

        int bestEvaluation = INT_MIN;

        std::vector<Move> moveList = moveGenerator->GenerateAllMoves();

        if(moveList.empty()) // if you have 0 moves, its either checkmate or stalemate
        {
            if(moveGenerator->IsInCheck())
                return INT_MIN; // worst possible eval for checkmate
            else
                return 0; // draw eval for stalemate
        }

        for (auto & move : moveList)
        {
            MovePositionInfo moveInfo = position->GenerateMoveInfo(move);
            position->MakeMove(move);
            int currentEvaluation = -Search(depth - 1);
            bestEvaluation = std::max(currentEvaluation, bestEvaluation);
            position->UndoMove(moveInfo);
        }

        return bestEvaluation;
    }
} // ChessEngine