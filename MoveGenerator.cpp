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

        PieceList* pieceList = (color == WHITE) ? board->whitePieces : board->blackPieces;
        std::vector<int> xList = pieceList->squaresX;
        std::vector<int> yList = pieceList->squaresY;

        for(int i = 0; i < pieceList->squaresX.size(); i++)
        {
            int x = xList[i];
            int y = yList[i];
            //std::cout << i << " " << pieceList[i].x << " " << pieceList[i].y << " " << pieceList[i].piece << std::endl;

            std::vector<Move> generatedMoves;
            generatedMoves = plMoveGenerator->GeneratePieceMoves(board->pieces[x][y], x, y);
            allGeneratedMoves = plMoveGenerator->CombineVectors(allGeneratedMoves, generatedMoves);
        }

        return allGeneratedMoves;
    }

    std::vector<Move> MoveGenerator::GeneratePieceMoves(ChessEngine::Piece piece, int startingX, int startingY)
    {
        PieceType pieceType = getType(piece);
        std::vector<Move> generatedMoves;
        std::vector<Move> additionalMoves;

        switch(pieceType)
        {
            case PAWN:
                generatedMoves = plMoveGenerator->GeneratePawnMoves(startingX, startingY);
                break;

            case BISHOP:
                generatedMoves = plMoveGenerator->GenerateDiagonalMoves(startingX, startingY);
                break;

            case KNIGHT:
                generatedMoves = plMoveGenerator->GenerateKnightMoves(startingX, startingY);
                break;

            case ROOK:
                generatedMoves = plMoveGenerator->GenerateStraightMoves(startingX, startingY);
                break;

            case QUEEN:
                generatedMoves = plMoveGenerator->GenerateStraightMoves(startingX, startingY);
                additionalMoves = plMoveGenerator->GenerateDiagonalMoves(startingX, startingY);
                generatedMoves = plMoveGenerator->CombineVectors(generatedMoves, additionalMoves);
                break;

            case KING:
                generatedMoves = GenerateKingMoves(startingX, startingY);
                additionalMoves = plMoveGenerator->GenerateCastlingMoves(startingX, startingY);
                generatedMoves = plMoveGenerator->CombineVectors(generatedMoves, additionalMoves);
                break;
        }

        return generatedMoves;
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

    std::vector<Move> MoveGenerator::GenerateKingMoves(int x, int y)
    {
        std::vector<Move> generatedMoves;
        Color color = getColor(position->board->pieces[x][y]);
        //bool threatMap[8][8] = (color == WHITE) ? blackThreatMap : whiteThreatMap;

        generatedMoves = plMoveGenerator->GenerateKingMoves(x, y);

        for(int i = 0; i < generatedMoves.size(); i++)
        {
            Move move = generatedMoves[i];
            if(color == WHITE)
            {
                if(blackThreatMap[move.destinationX][move.destinationY])
                    generatedMoves.erase(generatedMoves.begin() + i);
            }

            if(color == BLACK)
            {
                if(whiteThreatMap[move.destinationX][move.destinationY])
                    generatedMoves.erase(generatedMoves.begin() + i);
            }
        }

        return generatedMoves;
    }
} // ChessEngine