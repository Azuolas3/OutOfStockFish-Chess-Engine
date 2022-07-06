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
        int pieces[8][8] = { 0 };
    };
}

#endif //CHESS_ENGINE_CHESSBOARD_H
