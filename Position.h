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
        ChessBoard board;
        PieceColor activePlayerColor;

        bool whiteKingCastlingRights; // kingside
        bool whiteQueenCastlingRights; // queenside

        bool blackKingCastlingRights; // kingside
        bool blackQueenCastlingRights;

        int fiftyMoveRuleCounter;

        int enPassantSquareX;
        int enPassantSquareY;

    };
}



#endif //CHESS_ENGINE_POSITION_H
