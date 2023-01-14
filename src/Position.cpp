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

void Position::MakeMove(Move move)
{
    board->MovePiece(move);

    enPassantSquareX = -1;
    enPassantSquareY = -1;

    if(move.additionalAction != nullptr)
        move.additionalAction();

    activePlayerColor = (activePlayerColor == WHITE) ? BLACK : WHITE;
}

void Position::UndoMove(MovePositionInfo move)
{
    Move smallMove = move.move;

    board->MovePiece(InverseMove(smallMove));

    activePlayerColor = (activePlayerColor == WHITE) ? BLACK : WHITE;

    whiteCastlingRights = move.whiteCastlingRights;
    blackCastlingRights = move.blackCastlingRights;

    enPassantSquareX = move.enPassantSquare.x;
    enPassantSquareY = move.enPassantSquare.y;

    if(HasFlag(smallMove.moveType, CAPTURE))
    {
        board->AddPiece(move.capturedPiece, Square(smallMove.destinationX, smallMove.destinationY));
    }
    else if(HasFlag(move.move.moveType, CASTLING))
    {
        int rookFromX = (smallMove.startingX - smallMove.destinationX > 0) ? 3 : 5; // essentially checking whether it's a queenside or kingside castle
        int rookToX = (smallMove.startingX - smallMove.destinationX > 0) ? 0 : 7;

        int kingRank = smallMove.startingY;


        board->MovePiece(Move(rookFromX, kingRank, rookToX, kingRank));
    }
    else if (HasFlag(smallMove.moveType, EN_PASSANT))
    {
        Piece piece = (activePlayerColor == WHITE) ? W_PAWN : B_PAWN;

        int pawnY = (activePlayerColor == WHITE) ? 3 : 4;
        int pawnX = smallMove.destinationX;

        board->AddPiece(piece, Square(pawnX, pawnY));
    }

    if (IsPromotionType(smallMove.moveType))
    {
        Piece piece = (activePlayerColor == WHITE) ? W_PAWN : B_PAWN;
        board->ReplacePiece(piece, Square(smallMove.startingX, smallMove.startingY));
    }
}

MovePositionInfo Position::GenerateMoveInfo(Move move)
{
    MovePositionInfo moveInfo;
    moveInfo.move = move;

    if(board->pieces[move.destinationX][move.destinationY] != EMPTY)
    {
        moveInfo.capturedPiece = board->pieces[move.destinationX][move.destinationY];
        moveInfo.move.moveType = moveInfo.move.moveType | CAPTURE;
    }

    moveInfo.enPassantSquare = Square(enPassantSquareX, enPassantSquareY);
    moveInfo.whiteCastlingRights = whiteCastlingRights;
    moveInfo.blackCastlingRights = blackCastlingRights;

    return moveInfo;

}

void Position::SetEnPassantSquare(int x, int y)
{
    enPassantSquareX = x;
    enPassantSquareY = y;
}
