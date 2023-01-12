//
// Created by Azuolas on 7/5/2022.
//

#include "ChessBoard.h"

using namespace ChessEngine;

void ChessBoard::PrintBoard()
{
    std::map<Piece, wchar_t> symbolDictionary =
    {
            {EMPTY, L'\u26DA'}, //Unicode symbol codes for each piece and its color
            {B_PAWN, L'\u2659'},
            {W_PAWN, L'\u265F'},
            {B_BISHOP, L'\u2657'},
            {W_BISHOP, L'\u265D'},
            {B_KNIGHT, L'\u2658'},
            {W_KNIGHT, L'\u265E'},
            {B_ROOK, L'\u2656'},
            {W_ROOK, L'\u265C'},
            {B_QUEEN, L'\u2655'},
            {W_QUEEN, L'\u265B'},
            {B_KING, L'\u2654'},
            {W_KING, L'\u265A'}
    };

    for(int i = 7; i >= 0; i--)
    {
        for(int j = 0; j < 8; j++)
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD written = 0;
            // explicitly call the wide version (which always accepts UTF-16)
            WriteConsoleW(handle, &(symbolDictionary[pieces[j][i]]), 1, &written, NULL);
        }
        std::cout << std::endl;
    }
}

void ChessBoard::MovePiece(Move move)
{
    //std::cout << this << std::endl << fromX << " " << fromY << "   " << toX << " " << toY << std::endl;
    PieceList* pieceList = (GetColor(pieces[move.startingX][move.startingY]) == WHITE) ? whitePieces : blackPieces;
    PieceList* oppositePieceList = (GetColor(pieces[move.startingX][move.startingY]) == WHITE) ? blackPieces : whitePieces;

    pieceList->MovePiece(move.startingX, move.startingY, move.destinationX, move.destinationY);
    if(pieces[move.destinationX][move.destinationY] != EMPTY)
        oppositePieceList->RemovePiece(move.destinationX, move.destinationY);

    pieces[move.destinationX][move.destinationY] = pieces[move.startingX][move.startingY];
    pieces[move.startingX][move.startingY] = EMPTY;

}

void ChessBoard::RemovePiece(int x, int y)
{
    pieces[x][y] = EMPTY;
}
