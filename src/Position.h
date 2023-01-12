//
// Created by Azuolas on 7/9/2022.
//

#ifndef CHESS_ENGINE_POSITION_H
#define CHESS_ENGINE_POSITION_H

#include "ChessBoard.h"
#include <iostream>
#include "BoardUtility.h"

namespace ChessEngine
{
    class Position
    {
    public:
        ChessBoard* board;
        Color activePlayerColor;

        CastlingRights whiteCastlingRights = NONE;
        CastlingRights blackCastlingRights = NONE;

        int fiftyMoveRuleCounter;

        int enPassantSquareX = -1; // -1 to represent no square
        int enPassantSquareY = -1;

        void UndoMove(MovePositionInfo move);

        void RemoveCastlingRights(Color color, CastlingRights side);
        bool HasCastlingRights(Color color, CastlingRights side);
        MovePositionInfo GenerateMoveInfo(Move move);

        void SetEnPassantSquare(int x, int y);
    };
}



#endif //CHESS_ENGINE_POSITION_H
