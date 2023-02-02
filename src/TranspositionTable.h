//
// Created by Azuolas on 1/29/2023.
//

#ifndef CHESS_ENGINE_TRANSPOSITIONTABLE_H
#define CHESS_ENGINE_TRANSPOSITIONTABLE_H

#include "u64.h"
#include "Move.h"
#include "Position.h"

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
        u64 size;

    public:
        TranspositionTable(Position* position, u64 size = 63997) //odd 63997 size cause its better for size to be a prime
        {
            this->position = position;
            this->size = size;
        }

        u64 GetIndex();
        void ClearTable();
        int ReadHashEntry(int depth, int alpha, int beta);
        void RecordEntry(const Move &move, int eval, int depth, int flags);

        const int exactFlag = 0;
        const int betaFlag = 1;
        const int alphaFlag = 2;
        u64 times = 0;
        u64 otherTimes = 0;
        std::array<Entry, 63997> entries;
    };
} // ChessEngine

#endif //CHESS_ENGINE_TRANSPOSITIONTABLE_H
