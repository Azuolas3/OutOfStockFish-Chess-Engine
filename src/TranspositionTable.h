//
// Created by Azuolas on 1/29/2023.
//

#ifndef CHESS_ENGINE_TRANSPOSITIONTABLE_H
#define CHESS_ENGINE_TRANSPOSITIONTABLE_H

#include "u64.h"
#include "Move.h"
#include "Position.h"

#define NOT_FOUND INT_MIN

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
        Entry* entries;

        const int exact = 0;
        const int lowerBound = 1;
        const int upperBound = 2;

    public:
        TranspositionTable(Position* position, u64 size = 64000)
        {
            this->position = position;
            this->size = size;

            entries = new Entry[size];
        }

        u64 GetIndex();
        void ClearTable();
        int ReadHashEntry(int depth, int alpha, int beta);
        void RecordEntry(const Move &move, int eval, int depth, int flags);
    };
} // ChessEngine

#endif //CHESS_ENGINE_TRANSPOSITIONTABLE_H
