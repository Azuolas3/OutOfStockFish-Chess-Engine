//
// Created by Azuolas on 7/14/2022.
//

#include "MoveGenerator.h"

namespace ChessEngine
{
    std::vector<Move> MoveGenerator::GenerateAllMoves(Color color)
    {
        std::vector<Move> allGeneratedMoves;

        ChessBoard* board = position->board;

        std::vector<PieceInfo> pieceList = (color == WHITE) ? board->whitePieces : board->blackPieces;

        for(int i = 0; i < pieceList.size(); i++)
        {
            //std::cout << i << " " << pieceList[i].x << " " << pieceList[i].y << " " << pieceList[i].piece << std::endl;

            std::vector<Move> generatedMoves;
            generatedMoves = plMoveGenerator->GeneratePieceMoves(pieceList[i].piece, pieceList[i].x, pieceList[i].y);
            allGeneratedMoves = plMoveGenerator->CombineVectors(allGeneratedMoves, generatedMoves);
        }

        return allGeneratedMoves;
    }

    void MoveGenerator::InitThreatMaps(ChessBoard board)
    {
        std::vector<Move> whiteMoves = GenerateAllMoves(WHITE);
        std::vector<Move> blackMoves = GenerateAllMoves(BLACK);

        for(auto & whiteMove : whiteMoves)
        {
            whiteThreatMap[whiteMove.startingX][whiteMove.startingY] = true;
            whiteThreatMap[whiteMove.destinationX][whiteMove.destinationY] = true;
        }

        for(auto & blackMove : blackMoves)
        {
            blackThreatMap[blackMove.startingX][blackMove.startingY] = true;
            blackThreatMap[blackMove.destinationX][blackMove.destinationY] = true;
        }
    }
} // ChessEngine