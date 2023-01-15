//
// Created by Azuolas on 1/11/2023.
//

#include "PerftUtility.h"

namespace ChessEngine
{
    //static std::ofstream perftOutput("perft.txt");

    u64 Perft(int depth, Position *position, MoveGenerator *moveGenerator)
    {
        std::vector<Move> moveList;
        int moveCount;
        u64 nodes = 0;

        if(depth == 0)
            return 1ULL;

        moveList = moveGenerator->GenerateAllMoves();
        moveCount = moveList.size();

        for(int i = 0; i < moveCount; i++)
        {
            MovePositionInfo moveInfo = position->GenerateMoveInfo(moveList[i]);
            position->MakeMove(moveList[i]);
            //std::cout << "NODES: " << nodes << "  MOVE: " << MoveToString(moveList[i]) << " \n";
            nodes += Perft(depth - 1, position, moveGenerator);
            //std::cout << "NODES: " << nodes << "  MOVE: " << MoveToString(moveList[i]) << " " << position->board->blackPieces->count;
//            if(depth == 4 || depth == 3)
//            {
//                std::cout << " HOLY";
//            }
            //std::cout << std::endl;
            position->UndoMove(moveInfo);
        }

        return nodes;
    }
}