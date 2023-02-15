//
// Created by Azuolas on 1/12/2023.
//

#include "Move.h"

Move InverseMove(const Move& move)
{
    return Move(move.destinationX, move.destinationY, move.startingX, move.startingY);
}

ChessEngine::PieceType GetPieceTypeFromPromotionType(MoveType moveType)
{
    switch (moveType)
    {
        case B_PROMOTION:
            return ChessEngine::BISHOP;
        case N_PROMOTION:
            return ChessEngine::KNIGHT;
        case R_PROMOTION:
            return ChessEngine::ROOK;
        case Q_PROMOTION:
            return ChessEngine::QUEEN;
        default:
            return static_cast<ChessEngine::PieceType>(-1);
    }
}

MoveType GetMoveTypeFromChar(char c)
{
    switch(c)
    {
        case 'B':
            return B_PROMOTION;
        case 'N':
            return N_PROMOTION;
        case 'R':
            return R_PROMOTION;
        case 'Q':
            return Q_PROMOTION;
    }
}

char GetCharFromPromotionType(MoveType promotionType)
{
    switch(promotionType)
    {
        case B_PROMOTION:
            return 'b';
        case N_PROMOTION:
            return 'q';
        case R_PROMOTION:
            return 'r';
        case Q_PROMOTION:
            return 'q';
    }
}
