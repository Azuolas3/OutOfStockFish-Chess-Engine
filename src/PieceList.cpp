//
// Created by Azuolas on 7/15/2022.
//

#include "PieceList.h"

namespace ChessEngine
{
    void PieceList::AddPiece(int x, int y)
    {
        Square newPiece = Square(x, y);

        squares.push_back(newPiece);

        map[x][y] = count; // index, doesn't matter whether X or Y list
        count++;
    }

    void PieceList::RemovePiece(int x, int y)
    {
        int index = map[x][y];
        squares.erase(squares.begin() + index);
        map[x][y] = 0;
        count--;
    }

    void PieceList::MovePiece(int fromX, int fromY, int toX, int toY)
    {
        int index; //= map[toX][toY];

        index = map[fromX][fromY];
        squares[index].x = toX;
        squares[index].y = toY;
        map[toX][toY] = index;
    }
} // ChessEngine