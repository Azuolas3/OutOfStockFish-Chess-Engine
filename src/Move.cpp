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
