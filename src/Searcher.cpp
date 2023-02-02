//
// Created by Azuolas on 1/23/2023.
//

#include "Searcher.h"
#include "AlgebraicNotationUtility.h"

namespace ChessEngine
{
    int Searcher::Search(int depth, int alpha, int beta)
    {
        tt->times++;
        int ttLookup = tt->ReadHashEntry(depth, alpha, beta);

        if(ttLookup != NOT_FOUND)
        {
            //std::cout << bestEvaluation << '\n';
            transposFound++;
            return ttLookup;
        }

        if (depth == 0)
            return QuiescenceSearch(alpha, beta);


        std::vector<Move> moveList = moveGenerator->GenerateAllMoves(NORMAL);

        if(moveList.empty()) // if you have 0 moves, its either checkmate or stalemate
        {
            if(moveGenerator->IsInCheck())
                return INT_MIN + 1; // worst possible eval for checkmate
            else
                return 0; // draw eval for stalemate
        }

        Move bestMove;
        int evalFlag = tt->alphaFlag;
        for (auto & move : moveList)
        {
            MovePositionInfo moveInfo = position->GenerateMoveInfo(move);
            position->MakeMove(move);
            int currentEvaluation = -Search(depth - 1, -beta, -alpha);
            position->UndoMove(moveInfo);

            if(currentEvaluation >= beta)
            {
                if(depth >= 2)
                    tt->RecordEntry(move, beta, depth, tt->betaFlag);

                return beta;
            }
            if(currentEvaluation > alpha)
            {
                evalFlag = tt->exactFlag;
                bestMove = move;
                alpha = currentEvaluation;
            }
        }

        currentBestMove = bestMove;

        if(depth >= 2)
            tt->RecordEntry(bestMove, alpha, depth, evalFlag);

        return alpha;
    }

    int Searcher::QuiescenceSearch(int alpha, int beta)
    {
        posEvaluated++;
        int standPat = evaluator->EvaluatePosition();

        if(standPat >= beta)
            return beta;

        if(standPat < alpha - DELTA)
        {
            return alpha;
        }

        if(standPat > alpha)
            alpha = standPat;


        std::vector<Move> moveList = moveGenerator->GenerateAllMoves(CAPTURE_ONLY);

        std::sort(moveList.begin(), moveList.end(), [this](const Move& a, const Move& b){return this->SortCaptures(a, b);});
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

    bool Searcher::SortCaptures(const Move &leftMove, const Move &rightMove)
    {
        PieceType leftStartingPieceType = GetType(board->pieces[leftMove.startingX][leftMove.startingY]);
        PieceType leftCapturedPieceType = GetType(board->pieces[leftMove.destinationX][leftMove.destinationY]);

        PieceType rightStartingPieceType = GetType(board->pieces[rightMove.startingX][rightMove.startingY]);
        PieceType rightCapturedPieceType = GetType(board->pieces[rightMove.destinationX][rightMove.destinationY]);

        if(leftCapturedPieceType == 0 || rightCapturedPieceType == 0) // in case of any errors where a quiet move would be sorted
            return false;

        int leftHandCaptureValue = pieceValueMap[leftStartingPieceType] - pieceValueMap[leftCapturedPieceType];
        int rightHandCaptureValue = pieceValueMap[rightStartingPieceType] - pieceValueMap[rightCapturedPieceType];

        return leftHandCaptureValue < rightHandCaptureValue;
    }
} // ChessEngine