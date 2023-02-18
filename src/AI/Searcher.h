//
// Created by Azuolas on 1/23/2023.
//

#ifndef CHESS_ENGINE_SEARCHER_H
#define CHESS_ENGINE_SEARCHER_H

#include <limits>

#include "Evaluator.h"
#include "MoveGenerator/MoveGenerator.h"
#include "TranspositionTable.h"
#include "Utilities/TimerUtility.h"
#include "Utilities/AlgebraicNotationUtility.h"
#include "Utilities/InputReadUtility.h"

namespace ChessEngine
{
#define MATED (INT_MIN / 2 + 1000)
#define STARTING_VALUE (INT_MAX / 2)
#define MAX_DEPTH INT_MAX

    class Searcher
    {
        Evaluator *evaluator;
        MoveGenerator* moveGenerator;
        ChessBoard *board;

        bool isSearchRunning = true;

        void ReadInput();
        void PeriodicInputCheck(int ms);

    public:
        explicit Searcher(Evaluator* evaluator, MoveGenerator* moveGenerator)
        {
            this->evaluator = evaluator;
            this->moveGenerator = moveGenerator;

            position = evaluator->currentPosition;
            board = position->board;

            tt = new TranspositionTable(position);
            tt->ClearTable();
        }

        int Search(int depth, int alpha, int beta);
        int SearchIteratively(int allocatedSearchTime); // search using iterative deepening
        int QuiescenceSearch(int alpha, int beta); // search until you get a "quiet" position
        bool SortCaptures(const Move& firstMove, const Move& secondMove);
        bool SortMoves(const Move& firstMove, const Move& secondMove);
        int EvaluateCapture(const Move& capture);
        void OrderMoves(std::vector<Move> &moveList);
        void EndSearch();
        bool HasStopped();

        const int DELTA = pieceValueMap[ROOK]; // for delta pruning Quiescence search

        int maxDepth = MAX_DEPTH;

        Move currentBestMove;
        u64 posEvaluated = 0;
        u64 transposFound = 0;
        TranspositionTable* tt;
        Position *position;
    };

} // ChessEngine

#endif //CHESS_ENGINE_SEARCHER_H
