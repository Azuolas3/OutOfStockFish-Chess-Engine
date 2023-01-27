//
// Created by Azuolas on 1/27/2023.
//

#include "ZobristUtility.h"

void ChessEngine::InitializeZobrist()
{
    for(int square = 0; square < 64; square++)
    {
        for(int piece = 0; piece < 12; piece++)
        {
            pieceKeys[square][piece] = GetRandomU64Number();
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
                int square = x * 8 + y;

                int pieceIndex = (currentPiece / 4) - 1;
                if(GetColor(currentPiece) == BLACK)
                    pieceIndex += 6;

                key ^= pieceKeys[square][pieceIndex];
            }
        }
    }

    if(position->enPassantSquareX != -1)
        key ^= enPassantKeys[position->enPassantSquareX];

    int castleIndex = (position->whiteCastlingRights << 2) | position->blackCastlingRights;
    key ^= castleKeys[castleIndex];

    if(position->activePlayerColor == BLACK)
        key ^= sideToMoveKey;

    return key;
}
