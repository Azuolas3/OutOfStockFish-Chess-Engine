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
            u64 currNodes = 0;
            MovePositionInfo moveInfo = position->GenerateMoveInfo(moveList[i]);
            position->MakeMove(moveList[i]);
            //std::cout << "NODES: " << nodes << "  MOVE: " << MoveToString(moveList[i]) << " \n";
            currNodes = Perft(depth - 1, position, moveGenerator);
            nodes += currNodes;
            position->UndoMove(moveInfo);
            //std::cout << "NODES: " << currNodes << "  MOVE: " << MoveToString(moveList[i]) << " " << position->board->blackPieces->count;
            if(depth == 6)
            {
                std::cout << "NODES: " << currNodes << "  MOVE: " << MoveToString(moveList[i]) << " " << position->board->blackPieces->count << std::endl;
            }
            //std::cout << std::endl;
        }

        return nodes;
    }
}