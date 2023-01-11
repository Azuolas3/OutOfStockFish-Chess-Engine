//
// Created by Azuolas on 7/15/2022.
//

#ifndef CHESS_ENGINE_PIECELIST_H
#define CHESS_ENGINE_PIECELIST_H

#include <vector>
#include "BoardUtility.h"
//#include "Position.h"

namespace ChessEngine
{
    class PieceList
    {
        int map[8][8];


    public:
        void AddPiece(int x, int y);
        void RemovePiece(int x, int y);
        void MovePiece(int fromX, int fromY, int toX, int toY);

        std::vector<Square> squares;


        int count = 0;
    };

} // ChessEngine

#endif //CHESS_ENGINE_PIECELIST_H
