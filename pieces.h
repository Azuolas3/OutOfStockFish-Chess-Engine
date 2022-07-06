//
// Created by Azuolas on 7/5/2022.
//

#ifndef CHESS_ENGINE_PIECES_H
#define CHESS_ENGINE_PIECES_H

namespace ChessEngine
{
    enum PieceColor
    {
        BLACK, WHITE
    };

    const int pieceColorBitMask = 0b0001;

    enum PieceType
    {
        PAWN = 2,
        BISHOP = 4,
        KNIGHT = 6,
        ROOK = 8,
        QUEEN = 10,
        KING = 12
    };

    const int pieceTypeBitMask = 0b1110;

    enum Piece
    {
        EMPTY,
        B_PAWN = PAWN, W_PAWN,
        B_BISHOP, W_BISHOP,
        B_KNIGHT, W_KNIGHT,
        B_ROOK, W_ROOK,
        B_QUEEN, W_QUEEN,
        B_KING, W_KING
    };
}

#endif //CHESS_ENGINE_PIECES_H
