//
// Created by Azuolas on 1/29/2023.
//

#include "TranspositionTable.h"

namespace ChessEngine {
    u64 TranspositionTable::GetIndex()
    {
        return (position->zobristKey % size);
    }

    void TranspositionTable::ClearTable()
    {
        for(int i = 0; i < size; i++)
        {
            entries[i].key = 0ULL;
            entries[i].eval = 0;
            entries[i].depth = 0;
            entries[i].flags = 0;
            entries[i].eval = 0;
        }
    }

    int TranspositionTable::ReadHashEntry(int depth, int alpha, int beta)
    {
        Entry* entry = &entries[GetIndex()];
        if(position->zobristKey == entry->key)
        {
            //std::cout << "NE OMEGALUL" << '\n';

            if(depth <= entry->depth)
            {
                //return entry->eval;

                if(entry->flags == exactFlag)
                    return entry->eval;
                if(entry->flags == alphaFlag && entry->eval <= alpha)
                    return alpha;
                if(entry->flags == betaFlag && entry->eval >= beta)
                    return beta;
            }
        }
//        else if (entry->key != 0)
//            std::cout << "OMEGALUL" << '\n';

        return NOT_FOUND;
    }

    void TranspositionTable::RecordEntry(const Move &move, int eval, int depth, int flags)
    {
//        std::cout << GetIndex() << '\n';

        times++;
        Entry* entry = &entries[GetIndex()];

//        if(depth < entry->depth)
//            return;

        if(entry->key != 0)
        {
            int index = GetIndex();
            //std::cout << index<< '\n';
            //std::cout << "WHAT The fuck  " << entry->key << "  " << position->zobristKey << '\n';
            if(entry->key != position->zobristKey)
            {
                //std::cout << "ka blet" << '\n';
                otherTimes++;
            }
        }

//        if(entry->eval != 0)
//            std::cout << "WHAT The eval" << '\n';

        entry->key = position->zobristKey;
        entry->bestMove = move;
        entry->eval = eval;
        entry->depth = depth;
        entry->flags = flags;
    }
} // ChessEngine