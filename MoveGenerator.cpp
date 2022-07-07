//
// Created by Azuolas on 7/6/2022.
//

#include "MoveGenerator.h"

using namespace ChessEngine;
using std::vector;

vector<Move> MoveGenerator::GenerateStraightMoves(int startingX, int startingY)
{
    vector<Move> pseudoLegalMoves;

    // Horizontal moves
    for(int x = startingX + 1; x < 8; x++) // add moves to the right
    {
        Move move(startingX, startingY, x, startingY);

        if(board.pieces[x][startingY] != EMPTY)
        {
            if(getColor(board.pieces[startingX][startingY]) != getColor(board.pieces[x][startingY]))
                pseudoLegalMoves.push_back(move);
            break;
        }

        pseudoLegalMoves.push_back(move);
    }

    for(int x = startingX - 1; x >= 0; x--) // add moves to the left
    {
        Move move(startingX, startingY, x, startingY);

        if(board.pieces[x][startingY] != EMPTY)
        {
            if(getColor(board.pieces[startingX][startingY]) != getColor(board.pieces[x][startingY]))
                pseudoLegalMoves.push_back(move);
            break;
        }

        pseudoLegalMoves.push_back(move);
    }


    // Vertical moves
    for(int y = startingY + 1; y < 8; y++) // add moves going up
    {
        Move move(startingX, startingY, startingX, y);

        if(board.pieces[startingX][y] != EMPTY)
        {
            if(getColor(board.pieces[startingX][startingY]) != getColor(board.pieces[startingX][y]))
                pseudoLegalMoves.push_back(move);
            break;
        }

        pseudoLegalMoves.push_back(move);
    }

    for(int y = startingY - 1; y >= 0; y--) // add moves going down
    {
        Move move(startingX, startingY, startingX, y);

        if(board.pieces[startingX][y] != EMPTY)
        {
            if(getColor(board.pieces[startingX][startingY]) != getColor(board.pieces[startingX][y]))
                pseudoLegalMoves.push_back(move);
            break;
        }

        pseudoLegalMoves.push_back(move);
    }

    return pseudoLegalMoves;
}

std::vector<Move> MoveGenerator::GenerateDiagonalMoves(int startingX, int startingY)
{
    vector<Move> pseudoLegalMoves;

    // Upper right moves
    for(int x = startingX + 1, y = startingY + 1; x < 8 && y < 8; x++, y++) // add moves to the right
    {
        Move move(startingX, startingY, x, y);

        if(board.pieces[x][y] != EMPTY)
        {
            if(getColor(board.pieces[startingX][startingY]) != getColor(board.pieces[x][y]))
                pseudoLegalMoves.push_back(move);
            break;
        }

        pseudoLegalMoves.push_back(move);
    }

    // Upper left moves
    for(int x = startingX - 1, y = startingY + 1; x >= 0 && y < 8; x--, y++) // add moves to the right
    {
        Move move(startingX, startingY, x, y);

        if(board.pieces[x][y] != EMPTY)
        {
            if(getColor(board.pieces[startingX][startingY]) != getColor(board.pieces[x][y]))
                pseudoLegalMoves.push_back(move);
            break;
        }

        pseudoLegalMoves.push_back(move);
    }

    // Down right moves
    for(int x = startingX + 1, y = startingY - 1; x < 8 && y >= 0; x++, y--) // add moves to the right
    {
        Move move(startingX, startingY, x, y);

        if(board.pieces[x][y] != EMPTY)
        {
            if(getColor(board.pieces[startingX][startingY]) != getColor(board.pieces[x][y]))
                pseudoLegalMoves.push_back(move);
            break;
        }

        pseudoLegalMoves.push_back(move);
    }

    // Down left moves
    for(int x = startingX - 1, y = startingY - 1; x >= 0 && y >= 0; x--, y--) // add moves to the right
    {
        Move move(startingX, startingY, x, y);

        if(board.pieces[x][y] != EMPTY)
        {
            if(getColor(board.pieces[startingX][startingY]) != getColor(board.pieces[x][y]))
                pseudoLegalMoves.push_back(move);
            break;
        }

        pseudoLegalMoves.push_back(move);
    }

    return pseudoLegalMoves;
}
