//
// Created by Azuolas on 1/27/2023.
//

#ifndef CHESS_ENGINE_ZOBRISTUTILITY_H
#define CHESS_ENGINE_ZOBRISTUTILITY_H


#include <random>
#include "u64.h"
#include "Position.h"

namespace ChessEngine
{
    inline u64 pieceKeys[8][8][12];
    inline u64 castleKeys[16];
    inline u64 enPassantKeys[8];
    inline u64 sideToMoveKey;

    void InitializeZobrist();
    u64 GeneratePositionHashKey(Position* position);
    u64 GetRandomU64Number();

    int GetPieceIndex(Piece piece);
    int GetCastlingRightsIndex(CastlingRights white, CastlingRights black);
}



#endif //CHESS_ENGINE_ZOBRISTUTILITY_H
