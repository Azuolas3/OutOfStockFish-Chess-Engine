//
// Created by Azuolas on 1/23/2023.
//

#ifndef CHESS_ENGINE_SEARCHER_H
#define CHESS_ENGINE_SEARCHER_H

#include <limits>

#include "Evaluator.h"
#include "MoveGenerator.h"

namespace ChessEngine {

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

        int Search(int depth);

        Move currentBestMove;
    };


} // ChessEngine

#endif //CHESS_ENGINE_SEARCHER_H
