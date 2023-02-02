//
// Created by Azuolas on 7/9/2022.
//

#include "Position.h"
#include "ZobristUtility.h"

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

void Position::MakeMove(const Move& move)
{
    Piece movedPiece = board->pieces[move.startingX][move.startingY];
    Piece capturedPiece = board->pieces[move.destinationX][move.destinationY];

    int initialCastlingRightsIndex = GetCastlingRightsIndex(whiteCastlingRights, blackCastlingRights); // keeping track of index for zobrist hashing purposes

    if(capturedPiece != EMPTY)
    {
        zobristKey ^= pieceKeys[move.destinationX][move.destinationY][GetPieceIndex(capturedPiece)]; // removing captured piece in hash key
    }

    if(GetType(board->pieces[move.startingX][move.startingY]) == KING)
    {
        board->UpdateKingPosition(move, activePlayerColor);
    }

    board->MovePiece(move);

    if(enPassantSquareX != -1)
    {
        zobristKey ^= enPassantKeys[enPassantSquareX];

        enPassantSquareX = -1;
        enPassantSquareY = -1;
    }

    if(move.additionalAction != nullptr)
        move.additionalAction();

    if(enPassantSquareX != -1)
        zobristKey ^= enPassantKeys[enPassantSquareX];

    int newCastlingRightsIndex = GetCastlingRightsIndex(whiteCastlingRights, blackCastlingRights);
    if(initialCastlingRightsIndex != newCastlingRightsIndex) // check if castling rights have changed
    {
        zobristKey ^= castleKeys[initialCastlingRightsIndex];
        zobristKey ^= castleKeys[newCastlingRightsIndex];
    }
    if(HasFlag(move.moveType, CASTLING))
    {
        Piece rook = (activePlayerColor == WHITE) ? W_ROOK : B_ROOK;
        int rookToX = (move.startingX - move.destinationX > 0) ? 3 : 5; // essentially checking whether it's a queenside or kingside castle
        int rookFromX = (move.startingX - move.destinationX > 0) ? 0 : 7;

        int kingRank = move.startingY;

        zobristKey ^= pieceKeys[rookFromX][kingRank][GetPieceIndex(rook)];
        zobristKey ^= pieceKeys[rookToX][kingRank][GetPieceIndex(rook)];
    }
    else if (HasFlag(move.moveType, EN_PASSANT))
    {
        Piece pawn = (activePlayerColor == WHITE) ? B_PAWN : W_PAWN;

        int pawnY = (activePlayerColor == WHITE) ? 4 : 3;
        int pawnX = move.destinationX;

        zobristKey ^= pieceKeys[pawnX][pawnY][GetPieceIndex(pawn)];
    }
    else if (IsPromotionType(move.moveType))
    {
        Piece pawn = (activePlayerColor == WHITE) ? W_PAWN : B_PAWN;
        Piece promotedPiece = static_cast<Piece>(activePlayerColor | GetPieceTypeFromPromotionType(move.moveType));

        zobristKey ^= pieceKeys[move.destinationX][move.destinationY][GetPieceIndex(pawn)];
        zobristKey ^= pieceKeys[move.destinationX][move.destinationY][GetPieceIndex(promotedPiece)];
    }

    activePlayerColor = (activePlayerColor == WHITE) ? BLACK : WHITE;

    zobristKey ^= pieceKeys[move.startingX][move.startingY][GetPieceIndex(movedPiece)]; // moving piece in hash key
    zobristKey ^= pieceKeys[move.destinationX][move.destinationY][GetPieceIndex(movedPiece)]; // moving piece in hash key
    zobristKey ^= sideToMoveKey; // changing side to move in hash key


//    if(zobristKey != GeneratePositionHashKey(this))
//        std::cout << "WHAT THE HEEEEEEEEEELL MAKE" << '\n';
//    std::cout << "updated key: " << zobristKey << '\n';
//    std::cout << "should be:   " << GeneratePositionHashKey(this);
}

void Position::UndoMove(const MovePositionInfo& move)
{
    Move smallMove = move.move;
    Move inverseMove = InverseMove(smallMove);
    Color previousColor = (activePlayerColor == WHITE) ? BLACK : WHITE;

    Piece movedPiece = board->pieces[inverseMove.startingX][inverseMove.startingY];

    if(GetType(board->pieces[smallMove.destinationX][smallMove.destinationY]) == KING)
    {
        board->UpdateKingPosition(inverseMove, previousColor);
    }

    board->MovePiece(inverseMove);

    activePlayerColor = previousColor;

    int initialCastlingRightsIndex = GetCastlingRightsIndex(whiteCastlingRights, blackCastlingRights);
    int newCastlingRightsIndex = GetCastlingRightsIndex(move.whiteCastlingRights, move.blackCastlingRights);

    if(initialCastlingRightsIndex != newCastlingRightsIndex)
    {
        whiteCastlingRights = move.whiteCastlingRights;
        blackCastlingRights = move.blackCastlingRights;
        zobristKey ^= castleKeys[initialCastlingRightsIndex];
        zobristKey ^= castleKeys[newCastlingRightsIndex];
    }

    if(enPassantSquareX != move.enPassantSquare.x)
    {
        if(enPassantSquareX != -1)
            zobristKey ^= enPassantKeys[enPassantSquareX];
        if(move.enPassantSquare.x != -1)
            zobristKey ^= enPassantKeys[move.enPassantSquare.x];

        enPassantSquareX = move.enPassantSquare.x;
        enPassantSquareY = move.enPassantSquare.y;
    }

    if(HasFlag(smallMove.moveType, CAPTURE))
    {
        board->AddPiece(move.capturedPiece, Square(smallMove.destinationX, smallMove.destinationY));
        zobristKey ^= pieceKeys[smallMove.destinationX][smallMove.destinationY][GetPieceIndex(move.capturedPiece)];
    }
    else if(HasFlag(move.move.moveType, CASTLING))
    {
        Piece piece = (activePlayerColor == WHITE) ? W_ROOK : B_ROOK;

        int rookFromX = (smallMove.startingX - smallMove.destinationX > 0) ? 3 : 5; // essentially checking whether it's a queenside or kingside castle
        int rookToX = (smallMove.startingX - smallMove.destinationX > 0) ? 0 : 7;

        int kingRank = smallMove.startingY;


        board->MovePiece(Move(rookFromX, kingRank, rookToX, kingRank));
        zobristKey ^= pieceKeys[rookFromX][kingRank][GetPieceIndex(piece)];
        zobristKey ^= pieceKeys[rookToX][kingRank][GetPieceIndex(piece)];
    }
    else if (HasFlag(smallMove.moveType, EN_PASSANT))
    {
        Piece piece = (activePlayerColor == WHITE) ? B_PAWN : W_PAWN;

        int pawnY = (activePlayerColor == WHITE) ? 4 : 3;
        int pawnX = smallMove.destinationX;

        board->AddPiece(piece, Square(pawnX, pawnY));
        zobristKey ^= pieceKeys[pawnX][pawnY][GetPieceIndex(piece)];
    }

    if (IsPromotionType(smallMove.moveType))
    {
        Piece piece = (activePlayerColor == WHITE) ? W_PAWN : B_PAWN;
        board->ReplacePiece(piece, Square(smallMove.startingX, smallMove.startingY));
        zobristKey ^= pieceKeys[smallMove.startingX][smallMove.startingY][GetPieceIndex(movedPiece)];
        zobristKey ^= pieceKeys[smallMove.startingX][smallMove.startingY][GetPieceIndex(piece)];
    }

    zobristKey ^= pieceKeys[inverseMove.startingX][inverseMove.startingY][GetPieceIndex(movedPiece)]; // moving piece in hash key
    zobristKey ^= pieceKeys[inverseMove.destinationX][inverseMove.destinationY][GetPieceIndex(movedPiece)]; // moving piece in hash key
    zobristKey ^= sideToMoveKey;

//    if(zobristKey != GeneratePositionHashKey(this))
//        std::cout << "WHAT THE HEEEEEEEEEELL UNMAKE" << '\n';
//    std::cout << "updated key: " << zobristKey << '\n';
//    std::cout << "should be:   " << GeneratePositionHashKey(this);
}

MovePositionInfo Position::GenerateMoveInfo(const Move& move)
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

void Position::PerformCastling(const Move& rookMove, Color color)
{
    board->MovePiece(rookMove);
    RemoveCastlingRights(color, BOTH);
}
