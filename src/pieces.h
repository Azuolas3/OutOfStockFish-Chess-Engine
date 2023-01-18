//
// Created by Azuolas on 7/5/2022.
//

#ifndef CHESS_ENGINE_PIECES_H
#define CHESS_ENGINE_PIECES_H

namespace ChessEngine
{
    enum Color
    {
        BLACK = 1, WHITE
    };

    enum CastlingRights
    {
        NONE, KINGSIDE, QUEENSIDE, BOTH
    };

    const int pieceColorBitMask = 0b00011;

    enum PieceType
    {
        PAWN = 4, //0b00100
        BISHOP = 8, //0b01000
        KNIGHT = 12, //0b01100
        ROOK = 16, //0b10000
        QUEEN = 20, //0b10100
        KING = 24 //0b11000
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

    struct PieceInfo
    {
        Piece piece;
        int x, y;

        PieceInfo(Piece piece, int x, int y)
        {
            this->piece = piece;
            this->x = x;
            this->y = y;
        }
    };

    inline Color GetColor(Piece piece)
    {
        Color color = static_cast<Color>(piece & pieceColorBitMask);
        return color;
    }

    inline Color GetOppositeColor(Color color)
    {
        Color oppositeColor = color == WHITE ? BLACK : WHITE;
        return oppositeColor;
    }

    inline PieceType GetType(Piece piece)
    {
        PieceType type = static_cast<PieceType>(piece & pieceTypeBitMask);
        return type;
    }

    inline bool IsSlidingPiece(Piece piece)
    {
        if(GetType(piece) == ROOK || GetType(piece) == BISHOP ||  GetType(piece) == QUEEN)
            return true;
        else
            return false;
    }

    inline bool IsKing(Piece piece)
    {
        if(GetType(piece) == KING)
            return true;
        else
            return false;
    }

    inline bool IsPawn(Piece piece)
    {
        if(GetType(piece) == PAWN)
            return true;
        else
            return false;
    }

    inline bool IsRookOrQueen(Piece piece)
    {
        if(GetType(piece) == ROOK || GetType(piece) == QUEEN)
            return true;
        else
            return false;
    }

    inline bool IsRookOrQueen(Piece piece, Color color)
    {
        if((GetType(piece) == ROOK || GetType(piece) == QUEEN) && GetColor(piece) == color)
            return true;
        else
            return false;
    }

    inline bool IsBishopOrQueen(Piece piece)
    {
        if(GetType(piece) == BISHOP || GetType(piece) == QUEEN)
            return true;
        else
            return false;
    }

    inline bool IsBishopOrQueen(Piece piece, Color color)
    {
        if((GetType(piece) == BISHOP || GetType(piece) == QUEEN) && GetColor(piece) == color)
            return true;
        else
            return false;
    }
}

#endif //CHESS_ENGINE_PIECES_H
