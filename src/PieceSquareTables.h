//
// Created by Azuolas on 1/24/2023.
//

#ifndef CHESS_ENGINE_PIECESQUARETABLES_H
#define CHESS_ENGINE_PIECESQUARETABLES_H

#include <map>
#include <array>
#include "pieces.h"

using std::array;

namespace ChessEngine
{
    typedef array<array<int, 8>, 8> PieceSquareTable;

    const PieceSquareTable pawnTable =
    {{
         {0,  0,  0,  0,  0,  0,  0,  0},
         {70, 70, 70, 70, 70, 70, 70, 70},
         {25, 25, 30, 40, 40, 30, 25, 25},
         {5,  5,  10, 40, 40, 10,  5,  5},
         {0,  0,   0, 40, 40,  0,  0,  0},
         {5, -5, -10,  0,  0, -10, -5, 5},
         {20, 20, 15, -20, -20, 15, 20, 20},
         {0,  0,   0,   0,   0,  0,  0,  0}
    }};

    const PieceSquareTable knightTable =
    {{
         {-50, -40, -30, -30, -30, -30, -40, -50},
         {-40, -20,  0,   0,   0,   0,  -20, -40},
         {-30,  0,  10,  15,  15,  10,   0,  -30},
         {-30,  5,  20,  25,  25,  20,   5,  -30},
         {-30,  0,  15,  20,  20,  15,   0,  -30},
         {-30,  5,  -5,  15,  15,  10,   5,  -30},
         {-40, -20,  0,   5,   5,   0,  -20, -40},
         {-50, -40, -30, -30, -30, -30, -40, -50}
    }};

    const PieceSquareTable bishopTable =
    {{
         {-20, -10, -10, -10, -10, -10, -10, -20},
         {-10,  0,   0,   0,   0,   0,   0,  -10},
         {-10,  0,   5,  10,   10,  5,   0,  -10},
         {-10,  5,   5,  10,   10,  5,   5,  -10},
         {-10,  0,  10,  10,   10, 10,   0,  -10},
         {-10, 10,  10,  10,   10, 10,  10,  -10},
         {-10,  5,   0,   0,   0,  0,    5,  -10},
         {-20, -10, -10, -10, -10, -10, -10, -20}
    }};

    const PieceSquareTable rookTable =
    {{
         {0, 0, 0, 0, 0, 0, 0, 0},
         {5, 10, 10, 10, 10, 10, 10, 5},
         {-5, 0, 0, 0, 0, 0, 0, -5},
         {-5, 0, 0, 0, 0, 0, 0, -5},
         {-5, 0, 0, 0, 0, 0, 0, -5},
         {-5, 0, 0, 0, 0, 0, 0, -5},
         {-5, 0, 0, 0, 0, 0, 0, -5},
         {0, 0, 0, 5, 5, 0, 0, 0}
    }};

    const PieceSquareTable queenTable =
    {{
         {-20, -10, -10, -5, -5, -10, -10, -20},
         {-10, 0, 0, 0, 0, 0, 0, -10},
         {-10, 0, 5, 5, 5, 5, 0, -10},
         {-5, 0, 5, 5, 5, 5, 0, -5},
         {0, 0, 5, 5, 5, 5, 0, -5},
         {-10, 5, 5, 5, 5, 5, 0, -10},
         {-10, 0, 5, 0, 0, 0, 0, -10},
         {-20, -10, -10, -5, -5, -10, -10, -20}
    }};

    const PieceSquareTable kingTable =
    {{
         {-30, -40, -40, -50, -50, -40, -40, -30},
         {-30, -40, -40, -50, -50, -40, -40, -30},
         {-30, -40, -40, -50, -50, -40, -40, -30},
         {-30, -40, -40, -50, -50, -40, -40, -30},
         {-30, -30, -40, -40, -40, -40, -30, -30},
         {-10, -20, -20, -20, -20, -20, -20, -10},
         {35,  35,   0,   0,   0,   0,   35,  35},
         {60, 100,  85,   0,   0,  35,  100,  60}
    }};

    inline std::map<PieceType, PieceSquareTable> pieceValueMap =
    {
        {PAWN, pawnTable},
        {BISHOP, bishopTable},
        {KNIGHT, knightTable},
        {ROOK, rookTable},
        {QUEEN, queenTable},
        {KING, kingTable}
    };

    inline int GetPieceSquareValue(int x, int y, PieceType pieceType, Color color)
    {
        if(color == WHITE)
            y = 7 - y;

        array array1 = pieceValueMap[pieceType];
        return pieceValueMap[pieceType][y][x];
    }
}

#endif //CHESS_ENGINE_PIECESQUARETABLES_H
