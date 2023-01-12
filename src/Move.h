//
// Created by Azuolas on 1/12/2023.
//

#ifndef CHESS_ENGINE_MOVE_H
#define CHESS_ENGINE_MOVE_H

#include <functional>
#include "pieces.h"
#include "BoardUtility.h"

enum MoveType
{
    QUIET, CAPTURE, EN_PASSANT,
    CASTLING, PROMOTION
};

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
    ChessEngine::Square capturedPieceSquare;
    ChessEngine::Square enPassantSquare;
    ChessEngine::CastlingRights whiteCastlingRights;
    ChessEngine::CastlingRights blackCastlingRights;
};

Move InverseMove(const Move& move);


#endif //CHESS_ENGINE_MOVE_H
