//
// Created by Azuolas on 1/12/2023.
//

#ifndef CHESS_ENGINE_MOVE_H
#define CHESS_ENGINE_MOVE_H

#include <functional>
#include "pieces.h"
#include "BoardUtility.h"

enum MoveType // flags
{
    QUIET = 0,
    CAPTURE = 1,
    EN_PASSANT = 2,
    CASTLING = 4,
    B_PROMOTION = 8,
    N_PROMOTION = 16,
    R_PROMOTION = 32,
    Q_PROMOTION = 64
};

inline bool HasFlag(MoveType value, MoveType flagToCheck)
{
    return (value & flagToCheck) != 0;
}

inline bool IsPromotionType(MoveType value)
{
    return value >= B_PROMOTION;
}

inline MoveType operator|(MoveType a, MoveType b)
{
    return static_cast<MoveType>(static_cast<int>(a) | static_cast<int>(b));
}

struct Move
{
    Move()
    = default;

    Move(int fromX, int fromY, int toX, int toY, MoveType type = QUIET)
    {
        startingX = fromX;
        startingY = fromY;
        destinationX = toX;
        destinationY = toY;
        moveType = type;
    }

    int startingX, startingY;
    int destinationX, destinationY;

    MoveType moveType;
    std::function<void()> additionalAction = nullptr;
};

inline bool operator==(Move a, Move b)
{
    if(a.startingX == b.startingX && a.startingY == b.startingY && a.destinationX == b.destinationX && a.destinationY == b.destinationY && a.moveType == b.moveType)
        return true;

    return false;
}

struct MovePositionInfo // Larger struct which hols more information about a move, used for undoing a move
{
    MovePositionInfo()
    = default;

    MovePositionInfo(Move move, ChessEngine::Piece capturedPiece, ChessEngine::Square capturedPieceSquare, ChessEngine::Square enPassantSquare, ChessEngine::CastlingRights white, ChessEngine::CastlingRights black)
    {
        this->move = move;
        this->capturedPiece = capturedPiece;
        this->capturedPieceSquare = capturedPieceSquare;
        this->enPassantSquare = enPassantSquare;
        this->whiteCastlingRights = white;
        this->blackCastlingRights = black;
    }

    Move move;
    ChessEngine::Piece capturedPiece;
    ChessEngine::Square capturedPieceSquare{};
    ChessEngine::Square enPassantSquare{};
    ChessEngine::CastlingRights whiteCastlingRights;
    ChessEngine::CastlingRights blackCastlingRights;
};

Move InverseMove(const Move& move);
ChessEngine::PieceType GetPieceTypeFromPromotionType(MoveType moveType);
MoveType GetMoveTypeFromChar(char c);
char GetCharFromPromotionType(MoveType promotionType);


#endif //CHESS_ENGINE_MOVE_H
