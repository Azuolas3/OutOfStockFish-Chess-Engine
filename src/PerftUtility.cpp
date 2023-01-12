//
// Created by Azuolas on 1/11/2023.
//

#include "PerftUtility.h"

namespace ChessEngine
{
    u64 Perft(int depth, Position position, MoveGenerator moveGenerator)
    {
        std::vector<Move> moveList;
        int moveCount;
        u64 nodes = 0;

        if(depth == 0)
            return 1ULL;

        moveList = moveGenerator.GenerateAllMoves();
        moveCount = moveList.size();

        for(int i = 0; i < moveCount; i++)
        {
            position.board->MovePiece(moveList[i]);
        }
    }
}