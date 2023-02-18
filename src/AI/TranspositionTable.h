//
// Created by Azuolas on 1/29/2023.
//

#ifndef CHESS_ENGINE_TRANSPOSITIONTABLE_H
#define CHESS_ENGINE_TRANSPOSITIONTABLE_H

#include "Miscellaneous/u64.h"
#include "MoveGenerator/Move.h"
#include "BoardRepresentation/Position.h"

#define NOT_FOUND (INT_MIN+1000)

namespace ChessEngine
{
    struct Entry
    {
        u64 key;
        Move bestMove;
        int eval;
        int depth;
        int flags;
    };

    class TranspositionTable
    {
        Position* position;
        u64 size = 63997;

    public:
        TranspositionTable(Position *position)
        {
            this->position = position;
        }

        u64 GetIndex();
        void ClearTable();
        int ReadHashEntryEval(int depth, int alpha, int beta);
        Move ReadHashEntryMove();
        void RecordEntry(const Move &move, int eval, int depth, int flags);

        const int exactFlag = 0;
        const int betaFlag = 1;
        const int alphaFlag = 2;
        u64 times = 0;
        u64 otherTimes = 0;
        std::array<Entry, 63997> entries; //odd 63997 size cause it's better for size to be a prime to prevent collisions
    };
} // ChessEngine

#endif //CHESS_ENGINE_TRANSPOSITIONTABLE_H
