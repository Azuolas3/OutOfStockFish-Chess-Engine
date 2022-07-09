//
// Created by Azuolas on 7/9/2022.
//

#ifndef CHESS_ENGINE_POSITION_H
#define CHESS_ENGINE_POSITION_H

#include "ChessBoard.h"

namespace ChessEngine
{
    enum CastlingRights
    {
        NONE, KINGSIDE, QUEENSIDE, BOTH
    };


    class Position
    {
    public:
        ChessBoard board;
        PieceColor activePlayerColor;

        CastlingRights whiteCastlingRights = NONE;
        CastlingRights blackCastlingRights = NONE;

        int fiftyMoveRuleCounter;

        int enPassantSquareX;
        int enPassantSquareY;

        void RemoveCastlingRights(PieceColor color, CastlingRights side);
    };
}



#endif //CHESS_ENGINE_POSITION_H
