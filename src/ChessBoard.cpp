//
// Created by Azuolas on 7/5/2022.
//

#include "ChessBoard.h"

using namespace ChessEngine;

void ChessBoard::PrintBoard()
{
//    std::map<Piece, wchar_t> symbolDictionary =
//    {
//            {EMPTY, L'\u26DA'}, //Unicode symbol codes for each piece and its color
//            {B_PAWN, L'\u2659'},
//            {W_PAWN, L'\u265F'},
//            {B_BISHOP, L'\u2657'},
//            {W_BISHOP, L'\u265D'},
//            {B_KNIGHT, L'\u2658'},
//            {W_KNIGHT, L'\u265E'},
//            {B_ROOK, L'\u2656'},
//            {W_ROOK, L'\u265C'},
//            {B_QUEEN, L'\u2655'},
//            {W_QUEEN, L'\u265B'},
//            {B_KING, L'\u2654'},
//            {W_KING, L'\u265A'}
//    };

    std::map<Piece, char> symbolDictionary =
    {
            {EMPTY, ' '},
            {B_PAWN, 'p'},
            {W_PAWN, 'P'},
            {B_BISHOP, 'b'},
            {W_BISHOP, 'B'},
            {B_KNIGHT, 'n'},
            {W_KNIGHT, 'N'},
            {B_ROOK, 'r'},
            {W_ROOK, 'R'},
            {B_QUEEN, 'q'},
            {W_QUEEN, 'Q'},
            {B_KING, 'k'},
            {W_KING, 'K'}
    };

    std::cout << "\n +---+---+---+---+---+---+---+---+\n";
    for(int i = 7; i >= 0; i--)
    {
        for(int j = 0; j < 8; j++)
        {
            std::cout << " | " << symbolDictionary[pieces[j][i]];
        }

        std::cout << " | " << (1 + i) << "\n +---+---+---+---+---+---+---+---+\n";
    }

    std::cout << "   a   b   c   d   e   f   g   h\n";
}

void ChessBoard::MovePiece(const Move& move)
{
    Piece movingPiece = pieces[move.startingX][move.startingY];
    Piece moveToPiece = pieces[move.destinationX][move.destinationY];

    PieceList* pieceList = (GetColor(movingPiece) == WHITE) ? whitePieces : blackPieces;

    if(moveToPiece != EMPTY)
        RemovePiece(move.destinationX, move.destinationY);

    pieceList->MovePiece(move.startingX, move.startingY, move.destinationX, move.destinationY);

    pieces[move.destinationX][move.destinationY] = movingPiece;
    pieces[move.startingX][move.startingY] = EMPTY;

}

void ChessBoard::AddPiece(Piece piece, Square square)
{
    pieces[square.x][square.y] = piece;

    PieceList* pieceList = (GetColor(piece) == WHITE) ? whitePieces : blackPieces;
    pieceList->AddPiece(square.x, square.y);
}

void ChessBoard::RemovePiece(int x, int y)
{
    Color color = GetColor(pieces[x][y]);
    PieceList* pieceList = (color == WHITE) ? whitePieces : blackPieces;

    pieceList->RemovePiece(x, y);
    pieces[x][y] = EMPTY;
}

void ChessBoard::ReplacePiece(Piece piece, Square square)
{
    RemovePiece(square.x, square.y);
    AddPiece(piece, square);
}

void ChessBoard::UpdateKingPosition(const Move& move, Color color)
{
    if(color == WHITE)
    {
        whiteKingX = move.destinationX;
        whiteKingY = move.destinationY;
    }
    else if (color == BLACK)
    {
        blackKingX = move.destinationX;
        blackKingY = move.destinationY;
    }
}



