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

vector<Move> MoveGenerator::GenerateDiagonalMoves(int startingX, int startingY)
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

vector<Move> MoveGenerator::GenerateKnightMoves(int startingX, int startingY)
{
    vector<Move> pseudoLegalMoves;

    int xOffset[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int yOffset[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    for(int i = 0; i < 8; i++)
    {
        int x = startingX + xOffset[i];
        int y = startingY + yOffset[i];

        if(IsInBounds(x, y) && (!IsSameColor(startingX, startingY, x, y)))
        {
            Move move(startingX, startingY, x, y);
            pseudoLegalMoves.push_back(move);
        }
    }

/*    if(IsInBounds(startingX + 2, startingY + 1) && (!isSameColor(startingX, startingY, startingX +2, startingY + 1)))
    {
        Move move(startingX, startingY, startingX + 2, startingY + 1);
        pseudoLegalMoves.push_back(move);
    }

    if(IsInBounds(startingX + 1, startingY + 2) && (!isSameColor(startingX, startingY, startingX + 1, startingY + 2)))
    {
        Move move(startingX, startingY, startingX + 1, startingY + 2);
        pseudoLegalMoves.push_back(move);
    }

    if(IsInBounds(startingX + 2, startingY - 1) && (!isSameColor(startingX, startingY, startingX + 2, startingY - 1))
    {
        Move move(startingX, startingY, startingX + 2, startingY - 1);
        pseudoLegalMoves.push_back(move);
    }

    if(IsInBounds(startingX + 1, startingY - 2) && (!IsSameColor(startingX, startingY, startingX + 1, startingY - 2))
    {
        Move move(startingX, startingY, startingX + 1, startingY - 2);
        pseudoLegalMoves.push_back(move);
    }*/


    return pseudoLegalMoves;
}

vector<Move> MoveGenerator::GenerateKingMoves(int startingX, int startingY)
{
    vector<Move> pseudoLegalMoves;

    int xOffset[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int yOffset[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };

    for(int i = 0; i < 8; i++)
    {
        int x = startingX + xOffset[i];
        int y = startingY + yOffset[i];

        if(IsInBounds(x, y) && (!IsSameColor(startingX, startingY, x, y)))
        {
            Move move(startingX, startingY, x, y);
            pseudoLegalMoves.push_back(move);
        }
    }

    return pseudoLegalMoves;
}

vector<Move> MoveGenerator::GeneratePawnMoves(int startingX, int startingY)
{
    vector<Move> pseudoLegalMoves;

    int offset = (getColor(board.pieces[startingX][startingY]) == ChessEngine::WHITE) ? 1 : -1;
    int startingRank = (getColor(board.pieces[startingX][startingY]) == ChessEngine::WHITE) ? 1 : 6;
    Piece possibleSquare = board.pieces[startingX][startingY + offset];

    if(possibleSquare == EMPTY)
    {
        Move move(startingX, startingY, startingX, startingY + offset);
        pseudoLegalMoves.push_back(move);

        if(startingY == startingRank)
        {
            offset *= 2;
            Move move(startingX, startingY, startingX, startingY + offset);
            pseudoLegalMoves.push_back(move);
            offset /= 2;
        }
    }

    if(IsInBounds(startingX - 1, startingY + offset) && board.pieces[startingX - 1][startingY + offset] && !IsSameColor(startingX, startingY, startingX - 1, startingY + offset))
    {
        Move move(startingX, startingY, startingX - 1, startingY + offset);
        pseudoLegalMoves.push_back(move);
    }

    if(IsInBounds(startingX + 1, startingY + offset) && board.pieces[startingX + 1][startingY + offset] && !IsSameColor(startingX, startingY, startingX + 1, startingY + offset))
    {
        Move move(startingX, startingY, startingX + 1, startingY + offset);
        pseudoLegalMoves.push_back(move);
    }



    return pseudoLegalMoves;
}


bool MoveGenerator::IsSameColor(int startingX, int startingY, int destinationX, int destinationY)
{
    if(getColor(board.pieces[startingX][startingY]) == getColor(board.pieces[destinationX][destinationY]))
        return true;
    else
        return false;
}

bool MoveGenerator::IsInBounds(int x, int y)
{
    if ( x >= 0 && x <= 7 && y >= 0 && y <= 7)
        return true;
    else
        return false;
}