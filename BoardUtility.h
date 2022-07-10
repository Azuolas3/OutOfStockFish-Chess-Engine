//
// Created by Azuolas on 7/10/2022.
//

#ifndef CHESS_ENGINE_BOARDUTILITY_H
#define CHESS_ENGINE_BOARDUTILITY_H

#include "pieces.h"

namespace ChessEngine
{
    bool IsKingsideEmpty(Color color, Piece board[8][8]);
    bool IsQueensideEmpty(Color color, Piece board[8][8]);
}



#endif //CHESS_ENGINE_BOARDUTILITY_H
