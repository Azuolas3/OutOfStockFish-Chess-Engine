//
// Created by Azuolas on 7/15/2022.
//

#ifndef CHESS_ENGINE_PIECELIST_H
#define CHESS_ENGINE_PIECELIST_H

#include <vector>
#include "Utilities/BoardUtility.h"
//#include "Position.h"

namespace ChessEngine
{
    class PieceList
    {
        static const int maxPieceCount = 32;

    public:
        void AddPiece(int x, int y);
        void RemovePiece(int x, int y);
        void MovePiece(int fromX, int fromY, int toX, int toY);
        int map[8][8];

        Square squares[maxPieceCount];


        int count = 1;
    };

} // ChessEngine

#endif //CHESS_ENGINE_PIECELIST_H
