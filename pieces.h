//
// Created by Azuolas on 7/5/2022.
//

#ifndef CHESS_ENGINE_PIECES_H
#define CHESS_ENGINE_PIECES_H

#include <iostream>

namespace ChessEngine
{
    enum PieceColor
    {
        BLACK = 1, WHITE
    };

    const int pieceColorBitMask = 0b00011;

    enum PieceType
    {
        PAWN = 4,
        BISHOP = 8,
        KNIGHT = 12,
        ROOK = 16,
        QUEEN = 20,
        KING = 24
    };

    const int pieceTypeBitMask = 0b11100;

    enum Piece
    {
        EMPTY,
        B_PAWN = PAWN + BLACK, W_PAWN,
        B_BISHOP = BISHOP + BLACK, W_BISHOP,
        B_KNIGHT = KNIGHT + BLACK, W_KNIGHT,
        B_ROOK = ROOK + BLACK, W_ROOK,
        B_QUEEN = QUEEN + BLACK, W_QUEEN,
        B_KING = KING + BLACK, W_KING
    };

    inline PieceColor getColor(Piece piece)
    {
        PieceColor color = static_cast<PieceColor>(piece & pieceColorBitMask);
        return color;
    }

    inline PieceType getType(Piece piece)
    {
        PieceType type = static_cast<PieceType>(piece & pieceTypeBitMask);
        return type;
    }
}

#endif //CHESS_ENGINE_PIECES_H
