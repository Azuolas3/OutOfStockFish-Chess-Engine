//
// Created by Azuolas on 7/5/2022.
//

#ifndef CHESS_ENGINE_CHESSBOARD_H
#define CHESS_ENGINE_CHESSBOARD_H

#include "pieces.h"
#include <iostream>
#include "windows.h"
#include <map>
#include <vector>
#include "PieceList.h"
#include "Move.h"

namespace ChessEngine
{
    class ChessBoard
    {


    public:
        Piece pieces[8][8] = { EMPTY };
        PieceList* whitePieces = new PieceList();
        PieceList* blackPieces = new PieceList();

        int whiteKingX;
        int whiteKingY;

        int blackKingX;
        int blackKingY;

        void RemovePiece(int x, int y);
        void AddPiece(Piece piece, Square square);
        void MovePiece(Move move);
        void ReplacePiece(Piece piece, Square square);
        void PrintBoard();

        void UpdateKingPosition(const Move& move, Color color);
    };
}

#endif //CHESS_ENGINE_CHESSBOARD_H
