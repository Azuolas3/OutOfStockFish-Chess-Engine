//
// Created by Azuolas on 7/6/2022.
//

#include "PseudoLegalMoveGenerator.h"

using namespace ChessEngine;
using std::vector;

void PseudoLegalMoveGenerator::GenerateStraightMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, MoveGenerationType generationType)
{
    ChessBoard* board = position->board;
    Piece activePiece = board->pieces[startingX][startingY];
    Color activeColor = GetColor(activePiece);

    Piece activeKing = static_cast<Piece>(GetOppositeColor(activeColor) | KING);

    // Horizontal moves
    for(int x = startingX + 1; x < 8; x++) // add moves to the right
    {
        Move move(startingX, startingY, x, startingY);
        Piece currentPiece = board->pieces[x][startingY];

        if(currentPiece != EMPTY)
        {
            Color currentColor = GetColor(currentPiece);

            if(activeColor != currentColor || (generationType == THREAT_MAP && activeColor == currentColor))
            {
                pseudoLegalMoves.push_back(move);
                if(currentPiece != activeKing)
                    break;
            }
            if(generationType != THREAT_MAP || (generationType == THREAT_MAP && currentPiece != activeKing))
                break;
        }
        else if(generationType == CAPTURE_ONLY)
        {
            continue;
        }

        pseudoLegalMoves.push_back(move);
    }

    for(int x = startingX - 1; x >= 0; x--) // add moves to the left
    {
        Move move(startingX, startingY, x, startingY);
        Piece currentPiece = board->pieces[x][startingY];

        if(currentPiece != EMPTY)
        {
            Color currentColor = GetColor(currentPiece);

            if(activeColor != currentColor || (generationType == THREAT_MAP && activeColor == currentColor))
            {
                pseudoLegalMoves.push_back(move);
                if(currentPiece != activeKing)
                    break;
            }
            if(generationType != THREAT_MAP || (generationType == THREAT_MAP && currentPiece != activeKing))
                break;
        }
        else if(generationType == CAPTURE_ONLY)
        {
            continue;
        }

        pseudoLegalMoves.push_back(move);
    }


    // Vertical moves
    for(int y = startingY + 1; y < 8; y++) // add moves going up
    {
        Move move(startingX, startingY, startingX, y);
        Piece currentPiece = board->pieces[startingX][y];

        if(currentPiece != EMPTY)
        {
            Color currentColor = GetColor(currentPiece);

            if(activeColor != currentColor || (generationType == THREAT_MAP && activeColor == currentColor))
            {
                pseudoLegalMoves.push_back(move);
                if(currentPiece != activeKing)
                    break;
            }
            if(generationType != THREAT_MAP || (generationType == THREAT_MAP && currentPiece != activeKing))
                break;
        }
        else if(generationType == CAPTURE_ONLY)
        {
            continue;
        }

        pseudoLegalMoves.push_back(move);
    }

    for(int y = startingY - 1; y >= 0; y--) // add moves going down
    {
        Move move(startingX, startingY, startingX, y);
        Piece currentPiece = board->pieces[startingX][y];

        if(currentPiece != EMPTY)
        {
            Color currentColor = GetColor(currentPiece);

            if(activeColor != currentColor || (generationType == THREAT_MAP && activeColor == currentColor))
            {
                pseudoLegalMoves.push_back(move);
                if(currentPiece != activeKing)
                    break;
            }
            if(generationType != THREAT_MAP || (generationType == THREAT_MAP && currentPiece != activeKing))
                break;
        }
        else if(generationType == CAPTURE_ONLY)
        {
            continue;
        }

        pseudoLegalMoves.push_back(move);
    }
}

void PseudoLegalMoveGenerator::GenerateDiagonalMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, MoveGenerationType generationType)
{
    ChessBoard* board = position->board;
    Piece activePiece = board->pieces[startingX][startingY];
    Color activeColor = GetColor(activePiece);

    Piece activeKing = static_cast<Piece>(GetOppositeColor(activeColor) | KING);


    // Upper right moves
    for(int x = startingX + 1, y = startingY + 1; x < 8 && y < 8; x++, y++) // add moves to the right
    {
        Move move(startingX, startingY, x, y);
        Piece currentPiece = board->pieces[x][y];

        if(currentPiece != EMPTY)
        {
            Color currentColor = GetColor(currentPiece);

            if(activeColor != currentColor || (generationType == THREAT_MAP && activeColor == currentColor))
            {
                pseudoLegalMoves.push_back(move);
                if(currentPiece != activeKing)
                    break;
            }
            if(generationType != THREAT_MAP || (generationType == THREAT_MAP && currentPiece != activeKing))
                break;
        }
        else if(generationType == CAPTURE_ONLY)
        {
            continue;
        }

        pseudoLegalMoves.push_back(move);
    }

    // Upper left moves
    for(int x = startingX - 1, y = startingY + 1; x >= 0 && y < 8; x--, y++) // add moves to the right
    {
        Move move(startingX, startingY, x, y);
        Piece currentPiece = board->pieces[x][y];

        if(currentPiece != EMPTY)
        {
            Color currentColor = GetColor(currentPiece);

            if(activeColor != currentColor || (generationType == THREAT_MAP && activeColor == currentColor))
            {
                pseudoLegalMoves.push_back(move);
                if(currentPiece != activeKing)
                    break;
            }
            if(generationType != THREAT_MAP || (generationType == THREAT_MAP && currentPiece != activeKing))
                break;
        }
        else if(generationType == CAPTURE_ONLY)
        {
            continue;
        }

        pseudoLegalMoves.push_back(move);
    }

    // Down right moves
    for(int x = startingX + 1, y = startingY - 1; x < 8 && y >= 0; x++, y--) // add moves to the right
    {
        Move move(startingX, startingY, x, y);
        Piece currentPiece = board->pieces[x][y];

        if(currentPiece != EMPTY)
        {
            Color currentColor = GetColor(currentPiece);

            if(activeColor != currentColor || (generationType == THREAT_MAP && activeColor == currentColor))
            {
                pseudoLegalMoves.push_back(move);
                if(currentPiece != activeKing)
                    break;
            }
            if(generationType != THREAT_MAP || (generationType == THREAT_MAP && currentPiece != activeKing))
                break;
        }
        else if(generationType == CAPTURE_ONLY)
        {
            continue;
        }

        pseudoLegalMoves.push_back(move);
    }

    // Down left moves
    for(int x = startingX - 1, y = startingY - 1; x >= 0 && y >= 0; x--, y--) // add moves to the right
    {
        Move move(startingX, startingY, x, y);
        Piece currentPiece = board->pieces[x][y];

        if(currentPiece != EMPTY)
        {
            Color currentColor = GetColor(currentPiece);

            if(activeColor != currentColor || (generationType == THREAT_MAP && activeColor == currentColor))
            {
                pseudoLegalMoves.push_back(move);
                if(currentPiece != activeKing)
                    break;
            }
            if(generationType != THREAT_MAP || (generationType == THREAT_MAP && currentPiece != activeKing))
                break;
        }
        else if(generationType == CAPTURE_ONLY)
        {
            continue;
        }

        pseudoLegalMoves.push_back(move);
    }
}

void PseudoLegalMoveGenerator::GenerateKnightMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, MoveGenerationType generationType)
{
    int xOffset[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int yOffset[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    for(int i = 0; i < 8; i++)
    {
        int x = startingX + xOffset[i];
        int y = startingY + yOffset[i];

        Color color = GetColor(position->board->pieces[startingX][startingY]);
        Color currentColor = GetColor(position->board->pieces[x][y]);

        if(IsInBounds(x, y))
        {
            if(generationType == CAPTURE_ONLY && color != currentColor && position->board->pieces[x][y] != EMPTY)
            {
                Move move(startingX, startingY, x, y);
                pseudoLegalMoves.push_back(move);
            }
            else if(generationType != CAPTURE_ONLY && (color != currentColor || (generationType == THREAT_MAP && color == currentColor)))
            {
                Move move(startingX, startingY, x, y);
                pseudoLegalMoves.push_back(move);
            }
        }
    }
}

void PseudoLegalMoveGenerator::GenerateKingMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, MoveGenerationType generationType)
{
    int xOffset[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int yOffset[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };


    for(int i = 0; i < 8; i++)
    {
        int x = startingX + xOffset[i];
        int y = startingY + yOffset[i];

        Color color = GetColor(position->board->pieces[startingX][startingY]);
        Color currentColor = GetColor(position->board->pieces[x][y]);

        if(IsInBounds(x, y))
        {
            if(generationType == CAPTURE_ONLY && color != currentColor && position->board->pieces[x][y] != EMPTY)
            {
                Move move(startingX, startingY, x, y);
                pseudoLegalMoves.push_back(move);
            }
            else if(generationType != CAPTURE_ONLY && color != currentColor)
            {
                Move move(startingX, startingY, x, y);
                pseudoLegalMoves.push_back(move);
            }
        }
    }
}

void PseudoLegalMoveGenerator::GenerateCastlingMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY)
{
    ChessBoard* board = position->board;

    int kingRank = startingY;
    Color color = GetColor(board->pieces[startingX][startingY]);

    //Kingside generation
    if(IsKingsideEmpty(color, board->pieces) && position->HasCastlingRights(color, KINGSIDE) && GetType(board->pieces[7][kingRank]) == ROOK) // checking only for type because color doesnt matter - all castling conditions cant be met if the rook is of opposite color.
    {
        Move move(startingX, startingY, startingX + 2, startingY, CASTLING);
        pseudoLegalMoves.push_back(move);
    }

    //Queenside generation
    if(IsQueensideEmpty(color, board->pieces) && position->HasCastlingRights(color, QUEENSIDE) && GetType(board->pieces[0][kingRank]) == ROOK)
    {
        Move move(startingX, startingY, startingX - 2, startingY, CASTLING);
        pseudoLegalMoves.push_back(move);
    }
}

void PseudoLegalMoveGenerator::GeneratePawnMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, MoveGenerationType generationType)
{
    ChessBoard* board = position->board;
    Color pieceColor = GetColor(board->pieces[startingX][startingY]);

    int offset = (pieceColor == ChessEngine::WHITE) ? 1 : -1;
    int startingRank = pieceColor == ChessEngine::WHITE ? 1 : 6;
    int promotionRank = (pieceColor) == ChessEngine::WHITE ? 7 : 0;
    Piece possibleSquare = board->pieces[startingX][startingY + offset];

    if(generationType == NORMAL)
    {
        if(possibleSquare == EMPTY)
        {
            Move move(startingX, startingY, startingX, startingY + offset);

            if(startingY == startingRank && board->pieces[startingX][startingY + (offset * 2)] == EMPTY)
            {
                offset *= 2;
                Move move(startingX, startingY, startingX, startingY + offset);

                pseudoLegalMoves.push_back(move);
                offset /= 2;
            }

            if(move.destinationY == promotionRank)
            {
                for(int promotionType = B_PROMOTION, pieceType = BISHOP; promotionType <= Q_PROMOTION; promotionType *= 2, pieceType += 4)
                {
                    move.moveType = static_cast<MoveType>(promotionType);
                    pseudoLegalMoves.push_back(move);
                }
            }
            else
            {
                pseudoLegalMoves.push_back(move);
            }
        }
    }


    //capturing pieces
    if(IsInBounds(startingX - 1, startingY + offset))
    {
        Piece currentPiece = board->pieces[startingX - 1][startingY + offset];
        Color currentColor = GetColor(currentPiece);

        if((currentPiece != EMPTY && pieceColor != currentColor) || generationType == THREAT_MAP)
        {
            Move move(startingX, startingY, startingX - 1, startingY + offset);

            if(move.destinationY == promotionRank)
            {
                for(int promotionType = B_PROMOTION, pieceType = BISHOP; promotionType <= Q_PROMOTION; promotionType *= 2, pieceType += 4)
                {
                    move.moveType = static_cast<MoveType>(promotionType);
                    pseudoLegalMoves.push_back(move);
                }
            }
            else
            {
                pseudoLegalMoves.push_back(move);
            }
        }
    }

    if(IsInBounds(startingX + 1, startingY + offset))
    {
        Piece currentPiece = board->pieces[startingX + 1][startingY + offset];
        Color currentColor = GetColor(currentPiece);

        if((currentPiece != EMPTY && pieceColor != currentColor) || generationType == THREAT_MAP)
        {
            Move move(startingX, startingY, startingX + 1, startingY + offset);
            if(move.destinationY == promotionRank)
            {
                for(int promotionType = B_PROMOTION, pieceType = BISHOP; promotionType <= Q_PROMOTION; promotionType *= 2, pieceType += 4)
                {
                    move.moveType = static_cast<MoveType>(promotionType);
                    pseudoLegalMoves.push_back(move);
                }
            }
            else
            {
                pseudoLegalMoves.push_back(move);
            }
        }
    }

    // En Passant
    if(position->enPassantSquareX != -1)
    {
        if(IsInBounds(startingX + 1, startingY + offset) && (startingX + 1) == position->enPassantSquareX && (startingY + offset) == (position->enPassantSquareY)) //adding offset to squareY to make sure its equal with the target square
        {
            Move move(startingX, startingY, startingX + 1, startingY + offset, EN_PASSANT);
            pseudoLegalMoves.push_back(move);
        }

        if(IsInBounds(startingX - 1, startingY + offset) && (startingX - 1) == position->enPassantSquareX && (startingY + offset) == (position->enPassantSquareY))
        {
            Move move(startingX, startingY, startingX - 1, startingY + offset, EN_PASSANT);
            pseudoLegalMoves.push_back(move);
        }
    }
}

void PseudoLegalMoveGenerator::GeneratePieceMoves(std::vector<Move>& pseudoLegalMoves, ChessEngine::Piece piece, int startingX, int startingY, MoveGenerationType generationType)
{
    PieceType pieceType = GetType(piece);

    switch(pieceType)
    {
        case PAWN:
            GeneratePawnMoves(pseudoLegalMoves, startingX, startingY, generationType);
            break;

        case BISHOP:
            GenerateDiagonalMoves(pseudoLegalMoves, startingX, startingY, generationType);
            break;

        case KNIGHT:
            GenerateKnightMoves(pseudoLegalMoves, startingX, startingY, generationType);
            break;

        case ROOK:
            GenerateStraightMoves(pseudoLegalMoves, startingX, startingY, generationType);
            break;

        case QUEEN:
            GenerateStraightMoves(pseudoLegalMoves, startingX, startingY, generationType);
            GenerateDiagonalMoves(pseudoLegalMoves, startingX, startingY, generationType);
            break;

        case KING:
            GenerateKingMoves(pseudoLegalMoves, startingX, startingY);
            GenerateCastlingMoves(pseudoLegalMoves, startingX, startingY);
            break;
    }
}

std::vector<Move> PseudoLegalMoveGenerator::GenerateAllMoves(ChessEngine::Color color, MoveGenerationType generatesThreatMap)
{
    int maxSize = 256; // maximum theoretical number of moves is 218, 256 just in case and since it's a beautiful number :)

    std::vector<Move> generatedMoves;
    generatedMoves.reserve(maxSize);

    ChessBoard* board = position->board;

    PieceList* pieceList = (color == WHITE) ? board->whitePieces : board->blackPieces;
    Square* squareList = pieceList->squares;


    for(int i = 1; i < pieceList->count; i++)
    {
        int x = squareList[i].x;
        int y = squareList[i].y;

        GeneratePieceMoves(generatedMoves, board->pieces[x][y], x, y, generatesThreatMap);
    }

    return generatedMoves;
}
