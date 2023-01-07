//
// Created by Azuolas on 7/15/2022.
//

#include "PieceList.h"

namespace ChessEngine
{
    void PieceList::AddPiece(int x, int y)
    {
        squaresX.push_back(x);
        squaresY.push_back(y);

        map[x][y] = count; // index, doesn't matter whether X or Y list
        count++;
    }

    void PieceList::RemovePiece(int x, int y)
    {
        int index = map[x][y];
        squaresX.erase(squaresX.begin() + index);
        squaresY.erase(squaresY.begin() + index);
        map[x][y] = 0;
        count--;
    }

    void PieceList::MovePiece(int fromX, int fromY, int toX, int toY)
    {
        int index; //= map[toX][toY];

        index = map[fromX][fromY];
        squaresX[index] = toX;
        squaresY[index] = toY;
        map[toX][toY] = index;
    }
} // ChessEngine