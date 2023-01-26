//
// Created by Azuolas on 1/23/2023.
//

#include "Searcher.h"

namespace ChessEngine
{
    int Searcher::Search(int depth, int alpha, int beta)
    {
        if (depth == 0)
            return QuiescenceSearch(alpha, beta);

        int bestEvaluation = INT_MIN;

        std::vector<Move> moveList = moveGenerator->GenerateAllMoves();

        if(moveList.empty()) // if you have 0 moves, its either checkmate or stalemate
        {
            if(moveGenerator->IsInCheck())
                return INT_MIN + 1; // worst possible eval for checkmate
            else
                return 0; // draw eval for stalemate
        }

        Move bestMove;
        for (auto & move : moveList)
        {
            MovePositionInfo moveInfo = position->GenerateMoveInfo(move);
            position->MakeMove(move);
            int currentEvaluation = -Search(depth - 1, -beta, -alpha);
            if(currentEvaluation > bestEvaluation)
            {
                bestEvaluation = currentEvaluation;
                bestMove = move;
            }
            position->UndoMove(moveInfo);

            alpha = std::max(alpha, bestEvaluation);
            if(alpha > beta)
                break;
        }

        currentBestMove = bestMove;
        return bestEvaluation;
    }

    int Searcher::QuiescenceSearch(int alpha, int beta)
    {
        int eval = evaluator->EvaluatePosition();
        if(eval >= beta)
            return beta;
        if(eval > alpha)
            alpha = eval;

        std::vector<Move> moveList = moveGenerator->GenerateAllCaptureMoves();

        for (auto & move : moveList)
        {
            MovePositionInfo moveInfo = position->GenerateMoveInfo(move);
            position->MakeMove(move);
            int currentEvaluation = -QuiescenceSearch(-beta, -alpha);
            position->UndoMove(moveInfo);

            if (currentEvaluation >= beta)
                return beta;
            if(currentEvaluation > alpha)
                alpha = currentEvaluation;
        }

        return alpha;
    }
} // ChessEngine