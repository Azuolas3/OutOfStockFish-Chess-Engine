//
// Created by Azuolas on 1/27/2023.
//

#include "ZobristUtility.h"

void ChessEngine::InitializeZobrist()
{
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            for(int piece = 0; piece < 12; piece++)
            {
                pieceKeys[x][y][piece] = GetRandomU64Number();
            }
        }
    }

    for(int key = 0; key < 16; key++)
    {
        castleKeys[key] = GetRandomU64Number();
    }

    for(int key = 0; key < 8; key++)
    {
        enPassantKeys[key] = GetRandomU64Number();
    }

    sideToMoveKey = GetRandomU64Number();
}

u64 ChessEngine::GetRandomU64Number()
{
    std::random_device rd;

    /* Random number generator */
    std::default_random_engine generator(rd());

    /* Distribution on which to apply the generator */
    std::uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);

    return distribution(generator);
}

u64 ChessEngine::GeneratePositionHashKey(Position* position)
{
    u64 key = 0ULL;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            Piece currentPiece = position->board->pieces[x][y];

            if(currentPiece != EMPTY)
            {
                key ^= pieceKeys[x][y][GetPieceIndex(currentPiece)];
            }
        }
    }

    if(position->enPassantSquareX != -1)
        key ^= enPassantKeys[position->enPassantSquareX];

    int castleIndex = GetCastlingRightsIndex(position->whiteCastlingRights, position->blackCastlingRights);
    key ^= castleKeys[castleIndex];

    if(position->activePlayerColor == BLACK)
        key ^= sideToMoveKey;

    return key;
}

int ChessEngine::GetPieceIndex(ChessEngine::Piece piece)
{
    int pieceIndex = (piece / 4) - 1;
    if(GetColor(piece) == BLACK)
        pieceIndex += 6;

    return pieceIndex;
}

int ChessEngine::GetCastlingRightsIndex(ChessEngine::CastlingRights white, ChessEngine::CastlingRights black)
{
    int castleIndex = (white << 2) | black;
    return castleIndex;
}
