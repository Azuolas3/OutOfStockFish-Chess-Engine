//
// Created by Azuolas on 1/11/2023.
//

#include "PerftUtility.h"

namespace ChessEngine
{
    u64 Perft(int depth, Position *position, MoveGenerator *moveGenerator, bool isBulkCountingEnabled)
    {
        std::vector<Move> moveList;
        int moveCount;
        u64 nodes = 0;

        if(depth == 0)
            return 1ULL;

        if(isBulkCountingEnabled && depth == 1)
            return moveGenerator->GenerateAllMoves(NORMAL).size();

        moveList = moveGenerator->GenerateAllMoves(NORMAL);
        moveCount = moveList.size();

        for(int i = 0; i < moveCount; i++)
        {
            u64 currNodes = 0;
            MovePositionInfo moveInfo = position->GenerateMoveInfo(moveList[i]);
            position->MakeMove(moveList[i]);
            currNodes = Perft(depth - 1, position, moveGenerator, isBulkCountingEnabled);
            nodes += currNodes;
            position->UndoMove(moveInfo);
//            if(depth == 6)
//            {
//                std::cout << "NODES: " << currNodes << "  MOVE: " << MoveToString(moveList[i]) << " " << position->board->blackPieces->count << std::endl;
//            }
        }

        return nodes;
    }
}