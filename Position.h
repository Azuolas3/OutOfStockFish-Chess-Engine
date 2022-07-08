//
// Created by Azuolas on 7/9/2022.
//

#ifndef CHESS_ENGINE_POSITION_H
#define CHESS_ENGINE_POSITION_H

#include "ChessBoard.h"

namespace ChessEngine
{
    class Position
    {
    public:
        ChessBoard board;
        PieceColor activePlayerColor;

        bool whiteKingCastlingRights = false; // kingside
        bool whiteQueenCastlingRights = false; // queenside

        bool blackKingCastlingRights = false; // kingside
        bool blackQueenCastlingRights = false;

        int fiftyMoveRuleCounter;

        int enPassantSquareX;
        int enPassantSquareY;
    };
}



#endif //CHESS_ENGINE_POSITION_H
