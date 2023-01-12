//
// Created by Azuolas on 7/9/2022.
//

#include "Position.h"
using namespace ChessEngine;

void Position::RemoveCastlingRights(Color color, CastlingRights side)
{
    CastlingRights* sideRights = (color == WHITE) ? &whiteCastlingRights : &blackCastlingRights;

    *sideRights = static_cast<CastlingRights>(*sideRights & ~side);
}

bool Position::HasCastlingRights(Color color, CastlingRights side)
{
    CastlingRights castlingRights = (color == WHITE) ? whiteCastlingRights : blackCastlingRights;

    if(castlingRights == BOTH || castlingRights == side)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Position::UndoMove(MovePositionInfo move)
{
    board->MovePiece(InverseMove(move.move));
    board->AddPiece(move.capturedPiece, move.capturedPieceSquare);

    whiteCastlingRights = move.whiteCastlingRights;
    blackCastlingRights = move.blackCastlingRights;

    enPassantSquareX = move.enPassantSquare.x;
    enPassantSquareY = move.enPassantSquare.y;

    if(move.move.moveType == CASTLING)
    {
        int rookFromX = (move.move.startingX - move.move.destinationX > 0) ? 3 : 5; // essentially checking whether it's a queenside or kingside
        int rookToX = (move.move.startingX - move.move.destinationX > 0) ? 0 : 7;

        int kingRank = move.move.startingY; //


        board->MovePiece(Move(rookFromX, kingRank, rookToX, kingRank));
    }
}

MovePositionInfo Position::GenerateMoveInfo(Move move)
{
    MovePositionInfo moveInfo;
    moveInfo.move = move;

    return moveInfo;

}

void Position::SetEnPassantSquare(int x, int y)
{
    enPassantSquareX = x;
    enPassantSquareY = y;
}
