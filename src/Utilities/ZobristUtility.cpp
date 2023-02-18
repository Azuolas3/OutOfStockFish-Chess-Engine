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

unsigned int state = 1804289371;

unsigned int GetRandomU32Number()
{
    unsigned int number = state;

    number ^= number << 13;
    number ^= number >> 17;
    number ^= number << 5;

    state = number;

    return number;
}

u64 ChessEngine::GetRandomU64Number()
{
    u64 n1, n2, n3, n4;

    // init random numbers slicing 16 bits from MS1B side
    n1 = (u64)(GetRandomU32Number()) & 0xFFFF;
    n2 = (u64)(GetRandomU32Number()) & 0xFFFF;
    n3 = (u64)(GetRandomU32Number()) & 0xFFFF;
    n4 = (u64)(GetRandomU32Number()) & 0xFFFF;

    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
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

int ChessEngine::GetPieceIndex(ChessEngine::Piece piece) // slightly ugly code for converting a piece enum into an int index for pieceKeys[][][] array
{
    int pieceIndex = (piece / 4) - 1;
    if(GetColor(piece) == BLACK)
        pieceIndex += 6;

    return pieceIndex;
}

// converts castling rights into an index for castleKeys[] array
int ChessEngine::GetCastlingRightsIndex(ChessEngine::CastlingRights white, ChessEngine::CastlingRights black)
{
    int castleIndex = (white << 2) | black;
    return castleIndex;
}
