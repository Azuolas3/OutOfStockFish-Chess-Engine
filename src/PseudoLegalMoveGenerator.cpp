//
// Created by Azuolas on 7/6/2022.
//

#include "PseudoLegalMoveGenerator.h"

using namespace ChessEngine;
using std::vector;

vector<Move> PseudoLegalMoveGenerator::GenerateStraightMoves(int startingX, int startingY, bool generatesThreatMap)
{
    vector<Move> pseudoLegalMoves;
    ChessBoard board = (*position->board);

    // Horizontal moves
    for(int x = startingX + 1; x < 8; x++) // add moves to the right
    {
        Move move(startingX, startingY, x, startingY);

        if(board.pieces[x][startingY] != EMPTY)
        {
            if(!IsSameColor(startingX, startingY, x, startingY) || (generatesThreatMap && IsSameColor(startingX, startingY, x, startingY)))
                pseudoLegalMoves.push_back(move);
            if(!generatesThreatMap || (generatesThreatMap && GetType(board.pieces[x][startingY]) != KING))
                break;
        }

        pseudoLegalMoves.push_back(move);
    }

    for(int x = startingX - 1; x >= 0; x--) // add moves to the left
    {
        Move move(startingX, startingY, x, startingY);

        if(board.pieces[x][startingY] != EMPTY)
        {
            if(!IsSameColor(startingX, startingY, x, startingY) || (generatesThreatMap && IsSameColor(startingX, startingY, x, startingY)))
                pseudoLegalMoves.push_back(move);
            if(!generatesThreatMap || (generatesThreatMap && GetType(board.pieces[x][startingY]) != KING))
                break;
        }


        pseudoLegalMoves.push_back(move);
    }


    // Vertical moves
    for(int y = startingY + 1; y < 8; y++) // add moves going up
    {
        Move move(startingX, startingY, startingX, y);

        if(board.pieces[startingX][y] != EMPTY)
        {
            if(!IsSameColor(startingX, startingY, startingX, y) || (generatesThreatMap && IsSameColor(startingX, startingY, startingX, y)))
                pseudoLegalMoves.push_back(move);
            if(!generatesThreatMap || (generatesThreatMap && GetType(board.pieces[startingX][y]) != KING))
                break;
        }

        pseudoLegalMoves.push_back(move);
    }

    for(int y = startingY - 1; y >= 0; y--) // add moves going down
    {
        Move move(startingX, startingY, startingX, y);

        if(board.pieces[startingX][y] != EMPTY)
        {
            if(!IsSameColor(startingX, startingY, startingX, y) || (generatesThreatMap && IsSameColor(startingX, startingY, startingX, y)))
                pseudoLegalMoves.push_back(move);
            if(!generatesThreatMap || (generatesThreatMap && GetType(board.pieces[startingX][y]) != KING))
                break;
        }

        pseudoLegalMoves.push_back(move);
    }

    if(position->whiteCastlingRights != NONE && position->blackCastlingRights != NONE &&
            GetType(board.pieces[startingX][startingY]) == ROOK) // Adding RemoveCastleRights to each rook move
    {
        if(startingX == 0) // QUEENSIDE
        {
            Color color = GetColor(board.pieces[startingX][startingY]);
            std::function<void()> func = std::bind(&Position::RemoveCastlingRights, std::ref(position), color, QUEENSIDE);
            for(int i = 0; i < pseudoLegalMoves.size(); i++)
            {
                pseudoLegalMoves[i].additionalAction = func;
            }
        }

        if(startingX == 7) // KINGSIDE
        {
            Color color = GetColor(board.pieces[startingX][startingY]);
            std::function<void()> func = std::bind(&Position::RemoveCastlingRights, std::ref(position), color, KINGSIDE);
            for(int i = 0; i < pseudoLegalMoves.size(); i++)
            {
                pseudoLegalMoves[i].additionalAction = func;
            }
        }
    }

    return pseudoLegalMoves;
}

vector<Move> PseudoLegalMoveGenerator::GenerateDiagonalMoves(int startingX, int startingY, bool generatesThreatMap)
{
    vector<Move> pseudoLegalMoves;
    ChessBoard board = (*position->board);

    // Upper right moves
    for(int x = startingX + 1, y = startingY + 1; x < 8 && y < 8; x++, y++) // add moves to the right
    {
        Move move(startingX, startingY, x, y);

        if(board.pieces[x][y] != EMPTY)
        {
            if(!IsSameColor(startingX, startingY, x, y) || (generatesThreatMap && IsSameColor(startingX, startingY, x, y)))
                pseudoLegalMoves.push_back(move);
            if(!generatesThreatMap || (generatesThreatMap && GetType(board.pieces[x][y]) != KING))
                break;
        }

        pseudoLegalMoves.push_back(move);
    }

    // Upper left moves
    for(int x = startingX - 1, y = startingY + 1; x >= 0 && y < 8; x--, y++) // add moves to the right
    {
        Move move(startingX, startingY, x, y);

        if(board.pieces[x][y] != EMPTY)
        {
            if(!IsSameColor(startingX, startingY, x, y) || (generatesThreatMap && IsSameColor(startingX, startingY, x, y)))
                pseudoLegalMoves.push_back(move);
            if(!generatesThreatMap || (generatesThreatMap && GetType(board.pieces[x][y]) != KING))
                break;
        }

        pseudoLegalMoves.push_back(move);
    }

    // Down right moves
    for(int x = startingX + 1, y = startingY - 1; x < 8 && y >= 0; x++, y--) // add moves to the right
    {
        Move move(startingX, startingY, x, y);

        if(board.pieces[x][y] != EMPTY)
        {
            if(!IsSameColor(startingX, startingY, x, y) || (generatesThreatMap && IsSameColor(startingX, startingY, x, y)))
                pseudoLegalMoves.push_back(move);
            if(!generatesThreatMap || (generatesThreatMap && GetType(board.pieces[x][y]) != KING))
                break;
        }

        pseudoLegalMoves.push_back(move);
    }

    // Down left moves
    for(int x = startingX - 1, y = startingY - 1; x >= 0 && y >= 0; x--, y--) // add moves to the right
    {
        Move move(startingX, startingY, x, y);

        if(board.pieces[x][y] != EMPTY)
        {
            if(!IsSameColor(startingX, startingY, x, y) || (generatesThreatMap && IsSameColor(startingX, startingY, x, y)))
                pseudoLegalMoves.push_back(move);
            if(!generatesThreatMap || (generatesThreatMap && GetType(board.pieces[x][y]) != KING))
                break;
        }

        pseudoLegalMoves.push_back(move);
    }

    return pseudoLegalMoves;
}

vector<Move> PseudoLegalMoveGenerator::GenerateKnightMoves(int startingX, int startingY, bool generatesThreatMap)
{
    vector<Move> pseudoLegalMoves;

    int xOffset[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int yOffset[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    for(int i = 0; i < 8; i++)
    {
        int x = startingX + xOffset[i];
        int y = startingY + yOffset[i];

        if(IsInBounds(x, y) && (!IsSameColor(startingX, startingY, x, y) || (generatesThreatMap && IsSameColor(startingX, startingY, x, y))))
        {
            Move move(startingX, startingY, x, y);
            pseudoLegalMoves.push_back(move);
        }
    }

    return pseudoLegalMoves;
}

vector<Move> PseudoLegalMoveGenerator::GenerateKingMoves(int startingX, int startingY)
{
    vector<Move> pseudoLegalMoves;

    int xOffset[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int yOffset[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };


    for(int i = 0; i < 8; i++)
    {
        int x = startingX + xOffset[i];
        int y = startingY + yOffset[i];

        if(IsInBounds(x, y) && (!IsSameColor(startingX, startingY, x, y)))
        {
            Move move(startingX, startingY, x, y);
            Color color = GetColor(position->board->pieces[startingX][startingY]);
            move.additionalAction = std::bind(&Position::RemoveCastlingRights, std::ref(position), color, BOTH);
            pseudoLegalMoves.push_back(move);
        }
    }

    return pseudoLegalMoves;
}

std::vector<Move> PseudoLegalMoveGenerator::GenerateCastlingMoves(int startingX, int startingY)
{
    vector<Move> pseudoLegalMoves;
    ChessBoard board = (*position->board);

    int kingRank = startingY;
    Color color = GetColor(board.pieces[startingX][startingY]);

    //Kingside generation
    if(IsKingsideEmpty(color, board.pieces) && position->HasCastlingRights(color, KINGSIDE) && GetType(board.pieces[7][kingRank]) == ROOK) // checking only for type because color doesnt matter - all castling conditions cant be met if the rook is of opposite color.
    {
        Move move(startingX, startingY, startingX + 2, startingY);
        move.additionalAction = std::bind(&ChessBoard::MovePiece, std::ref(position->board), 7, kingRank, 5, kingRank);
        pseudoLegalMoves.push_back(move);
    }

    //Queenside generation
    if(IsQueensideEmpty(color, board.pieces) && position->HasCastlingRights(color, QUEENSIDE) && GetType(board.pieces[0][kingRank]) == ROOK)
    {
        Move move(startingX, startingY, startingX - 2, startingY);
        move.additionalAction = std::bind(&ChessBoard::MovePiece, std::ref(position->board), 0, kingRank, 3, kingRank);
        pseudoLegalMoves.push_back(move);
    }

    return pseudoLegalMoves;
}

vector<Move> PseudoLegalMoveGenerator::GeneratePawnMoves(int startingX, int startingY, bool generatesOnlyCaptures)
{
    vector<Move> pseudoLegalMoves;
    ChessBoard board = (*position->board);

    int offset = (GetColor(board.pieces[startingX][startingY]) == ChessEngine::WHITE) ? 1 : -1;
    int startingRank = (GetColor(board.pieces[startingX][startingY]) == ChessEngine::WHITE) ? 1 : 6;
    Piece possibleSquare = board.pieces[startingX][startingY + offset];

    if(!generatesOnlyCaptures)
    {
        if(possibleSquare == EMPTY)
        {
            Move move(startingX, startingY, startingX, startingY + offset);
            pseudoLegalMoves.push_back(move);

            if(startingY == startingRank)
            {
                offset *= 2;
                Move move(startingX, startingY, startingX, startingY + offset);
                move.additionalAction = std::bind(&Position::SetEnPassantSquare, std::ref(position), startingX, startingY + (offset/2));
                pseudoLegalMoves.push_back(move);
                offset /= 2;
            }
        }
    }


    if(IsInBounds(startingX - 1, startingY + offset))
    {
        if((board.pieces[startingX - 1][startingY + offset] && !IsSameColor(startingX, startingY, startingX - 1, startingY + offset)) || generatesOnlyCaptures)
        {
            Move move(startingX, startingY, startingX - 1, startingY + offset);
            pseudoLegalMoves.push_back(move);
        }
    }

    if(IsInBounds(startingX + 1, startingY + offset))
    {
        if((board.pieces[startingX + 1][startingY + offset] && !IsSameColor(startingX, startingY, startingX + 1, startingY + offset)) || generatesOnlyCaptures)
        {
            Move move(startingX, startingY, startingX + 1, startingY + offset);
            pseudoLegalMoves.push_back(move);
        }
    }

    // En Passant
    if(position->enPassantSquareX != -1)
    {
        if(IsInBounds(startingX + 1, startingY + offset) && (startingX + 1) == position->enPassantSquareX && (startingY + offset) == (position->enPassantSquareY)) //adding offset to squareY to make sure its equal with the target square
        {
            Move move(startingX, startingY, startingX + 1, startingY + offset);
            move.additionalAction = std::bind(&ChessBoard::RemovePiece, std::ref(position->board), position->enPassantSquareX, startingY);
            pseudoLegalMoves.push_back(move);
        }

        if(IsInBounds(startingX - 1, startingY + offset) && (startingX - 1) == position->enPassantSquareX && (startingY + offset) == (position->enPassantSquareY))
        {
            Move move(startingX, startingY, startingX - 1, startingY + offset);
            move.additionalAction = std::bind(&ChessBoard::RemovePiece, std::ref(position->board), startingX - 1, startingY);
            pseudoLegalMoves.push_back(move);
        }
    }


    return pseudoLegalMoves;
}

std::vector<Move> PseudoLegalMoveGenerator::GeneratePieceMoves(ChessEngine::Piece piece, int startingX, int startingY, bool ignoresEnemyKing)
{
    PieceType pieceType = GetType(piece);
    std::vector<Move> generatedMoves;
    std::vector<Move> additionalMoves;

    switch(pieceType)
    {
        case PAWN:
            generatedMoves = GeneratePawnMoves(startingX, startingY, ignoresEnemyKing);
            break;

        case BISHOP:
            generatedMoves = GenerateDiagonalMoves(startingX, startingY, ignoresEnemyKing);
            break;

        case KNIGHT:
            generatedMoves = GenerateKnightMoves(startingX, startingY);
            break;

        case ROOK:
            generatedMoves = GenerateStraightMoves(startingX, startingY, ignoresEnemyKing);
            break;

        case QUEEN:
            generatedMoves = GenerateStraightMoves(startingX, startingY, ignoresEnemyKing);
            additionalMoves = GenerateDiagonalMoves(startingX, startingY, ignoresEnemyKing);
            generatedMoves = CombineVectors(generatedMoves, additionalMoves);
            break;

        case KING:
            generatedMoves = GenerateKingMoves(startingX, startingY);
            additionalMoves = GenerateCastlingMoves(startingX, startingY);
            generatedMoves = CombineVectors(generatedMoves, additionalMoves);
            break;
    }

    return generatedMoves;
}

bool PseudoLegalMoveGenerator::IsSameColor(int startingX, int startingY, int destinationX, int destinationY)
{
    ChessBoard board = (*position->board);

    if(GetColor(board.pieces[startingX][startingY]) == GetColor(board.pieces[destinationX][destinationY]))
        return true;
    else
        return false;
}

std::vector<Move> PseudoLegalMoveGenerator::CombineVectors(std::vector<Move> a, std::vector<Move> b)
{
    std::vector<Move> combinedVector;
    combinedVector.reserve( a.size() + b.size());
    combinedVector.insert(combinedVector.end(), a.begin(), a.end());
    combinedVector.insert( combinedVector.end(), b.begin(), b.end() );
    return combinedVector;
}

bool PseudoLegalMoveGenerator::doesContainMove(std::vector<Move> generatedMoves, Square start, Square end, Move* correctMove)
{
    for(int i = 0; i < generatedMoves.size(); i++)
    {
        if(generatedMoves[i].destinationX == end.x && generatedMoves[i].destinationY == end.y && generatedMoves[i].startingX == start.x && generatedMoves[i].startingY == start.y)
        {
            *correctMove = generatedMoves[i];
            return true;
        }
    }
    return false;
}

std::vector<Move> PseudoLegalMoveGenerator::GenerateAllMoves(ChessEngine::Color color, bool generatesThreatMap)
{
    std::vector<Move> allGeneratedMoves;

    ChessBoard* board = position->board;

    PieceList* pieceList = (color == WHITE) ? board->whitePieces : board->blackPieces;
    std::vector<Square> squareList = pieceList->squares;


    for(int i = 0; i < pieceList->squares.size(); i++)
    {
        int x = squareList[i].x;
        int y = squareList[i].y;
        //std::cout << i << " " << pieceList[i].x << " " << pieceList[i].y << " " << pieceList[i].piece << std::endl;

        std::vector<Move> generatedMoves;
        generatedMoves = GeneratePieceMoves(board->pieces[x][y], x, y, generatesThreatMap);
        allGeneratedMoves = CombineVectors(allGeneratedMoves, generatedMoves);
    }

    return allGeneratedMoves;
}
