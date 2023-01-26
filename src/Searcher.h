//
// Created by Azuolas on 1/23/2023.
//

#ifndef CHESS_ENGINE_SEARCHER_H
#define CHESS_ENGINE_SEARCHER_H

#include <limits>

#include "Evaluator.h"
#include "MoveGenerator.h"

namespace ChessEngine
{

    class Searcher
    {
        Evaluator *evaluator;
        MoveGenerator* moveGenerator;
        Position *position;
        ChessBoard *board;

    public:
        explicit Searcher(Evaluator* evaluator, MoveGenerator* moveGenerator)
        {
            this->evaluator = evaluator;
            this->moveGenerator = moveGenerator;

            position = evaluator->currentPosition;
            board = position->board;
        }

        int Search(int depth, int alpha, int beta);
        int QuiescenceSearch(int alpha, int beta);
        bool SortCaptures(const Move& leftMove, const Move& rightMove);

        const int DELTA = pieceValueMap[QUEEN]; // for delta pruning Quiescence search

        Move currentBestMove;
        int posEvaluated = 0;
    };

} // ChessEngine

#endif //CHESS_ENGINE_SEARCHER_H
