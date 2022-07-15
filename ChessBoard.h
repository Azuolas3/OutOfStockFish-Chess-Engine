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

namespace ChessEngine
{
    class ChessBoard
    {

        void RemovePieceFromList(int x, int y);
    public:
        Piece pieces[8][8] = { EMPTY };
        PieceList* whitePieces = new PieceList();
        PieceList* blackPieces = new PieceList();

        void RemovePiece(int x, int y);
        void MovePiece(int fromX, int fromY, int toX, int toY);
        void PrintBoard();
    };
}

#endif //CHESS_ENGINE_CHESSBOARD_H
