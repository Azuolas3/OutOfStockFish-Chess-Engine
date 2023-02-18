//
// Created by Azuolas on 1/23/2023.
//

#include "Evaluator.h"

namespace ChessEngine
{
    float Evaluator::EvaluatePosition()
    {
        int whiteEval = GetMaterialCount(WHITE);
        int blackEval = GetMaterialCount(BLACK);

        whiteEval += EvaluatePieceSquareTables(WHITE);
        blackEval += EvaluatePieceSquareTables(BLACK);

        int evaluation = whiteEval - blackEval;

        if(currentPosition->activePlayerColor == BLACK)
            evaluation *= -1;

        return evaluation;
    }

    int Evaluator::GetMaterialCount(Color side)
    {
        int totalMaterial = 0;

        PieceList* pieceList = (side == WHITE) ? currentBoard->whitePieces : currentBoard->blackPieces;
        Square* squareList = pieceList->squares;

        for(int i = 1; i < pieceList->count; i++)
        {
            int x = squareList[i].x;
            int y = squareList[i].y;

            PieceType currentPieceType = GetType(currentBoard->pieces[x][y]);
            totalMaterial += pieceValueMap[currentPieceType];
        }

        return totalMaterial;
    }

    int Evaluator::EvaluatePieceSquareTables(Color side)
    {
        int eval = 0;

        PieceList* pieceList = (side == WHITE) ? currentBoard->whitePieces : currentBoard->blackPieces;
        Square* squareList = pieceList->squares;

        for(int i = 1; i < pieceList->count; i++)
        {
            int x = squareList[i].x;
            int y = squareList[i].y;

            PieceType currentPieceType = GetType(currentBoard->pieces[x][y]);
            eval += GetPieceSquareValue(x, y, currentPieceType, side);
        }

        return eval;
    }
} // ChessEngine