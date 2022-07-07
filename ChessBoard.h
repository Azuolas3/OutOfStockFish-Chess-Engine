//
// Created by Azuolas on 7/5/2022.
//

#ifndef CHESS_ENGINE_CHESSBOARD_H
#define CHESS_ENGINE_CHESSBOARD_H

#include "pieces.h"
#include <iostream>
#include "windows.h"
#include <map>

namespace ChessEngine
{
    class ChessBoard
    {
    public:
        void printBoard();
        Piece pieces[8][8] = { EMPTY };
    };
}

#endif //CHESS_ENGINE_CHESSBOARD_H
