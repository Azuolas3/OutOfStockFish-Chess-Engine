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
    Color activeColor = GetColor(board.pieces[startingX][startingY]);

    Piece activeKing = static_cast<Piece>(GetOppositeColor(activeColor) | KING);

    // Horizontal moves
    for(int x = startingX + 1; x < 8; x++) // add moves to the right
    {
        Move move(startingX, startingY, x, startingY);

        if(board.pieces[x][startingY] != EMPTY)
        {
            if(!IsSameColor(startingX, startingY, x, startingY) || (generatesThreatMap && IsSameColor(startingX, startingY, x, startingY)))
            {
                pseudoLegalMoves.push_back(move);
                if(board.pieces[x][startingY] != activeKing)
                    break;
            }
            if(!generatesThreatMap || (generatesThreatMap && board.pieces[x][startingY] != activeKing))
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
            {
                pseudoLegalMoves.push_back(move);
                if(board.pieces[x][startingY] != activeKing)
                    break;
            }
            if(!generatesThreatMap || (generatesThreatMap && board.pieces[x][startingY] != activeKing))
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
            {
                pseudoLegalMoves.push_back(move);
                if(board.pieces[startingX][y] != activeKing)
                    break;
            }
            if(!generatesThreatMap || (generatesThreatMap && board.pieces[startingX][y] != activeKing))
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
            {
                pseudoLegalMoves.push_back(move);
                if(board.pieces[startingX][y] != activeKing)
                    break;
            }
            if(!generatesThreatMap || (generatesThreatMap && board.pieces[startingX][y] != activeKing))
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
            std::function<void()> func = [color, this] { position->RemoveCastlingRights(color, QUEENSIDE); };
            for(int i = 0; i < pseudoLegalMoves.size(); i++)
            {
                pseudoLegalMoves[i].additionalAction = func;
            }
        }

        if(startingX == 7) // KINGSIDE
        {
            Color color = GetColor(board.pieces[startingX][startingY]);
            std::function<void()> func = [color, this] { position->RemoveCastlingRights(color, KINGSIDE); };
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
    Color activeColor = GetColor(board.pieces[startingX][startingY]);

    Piece activeKing = static_cast<Piece>(GetOppositeColor(activeColor) | KING);


    // Upper right moves
    for(int x = startingX + 1, y = startingY + 1; x < 8 && y < 8; x++, y++) // add moves to the right
    {
        Move move(startingX, startingY, x, y);

        if(board.pieces[x][y] != EMPTY)
        {
            if(!IsSameColor(startingX, startingY, x, y) || (generatesThreatMap && IsSameColor(startingX, startingY, x, y)))
            {
                pseudoLegalMoves.push_back(move);
                if(board.pieces[x][y] != activeKing)
                    break;
            }
            if(!generatesThreatMap || (generatesThreatMap && board.pieces[x][y] != activeKing))
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
            {
                pseudoLegalMoves.push_back(move);
                if(board.pieces[x][y] != activeKing)
                    break;
            }
            if(!generatesThreatMap || (generatesThreatMap && board.pieces[x][y] != activeKing))
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
            {
                pseudoLegalMoves.push_back(move);
                if(board.pieces[x][y] != activeKing)
                    break;
            }
            if(!generatesThreatMap || (generatesThreatMap && board.pieces[x][y] != activeKing))
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
            {
                pseudoLegalMoves.push_back(move);
                if(board.pieces[x][y] != activeKing)
                    break;
            }
            if(!generatesThreatMap || (generatesThreatMap && board.pieces[x][y] != activeKing))
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
            move.additionalAction = [this, color] { position->RemoveCastlingRights(color, BOTH); };
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
        Move move(startingX, startingY, startingX + 2, startingY, CASTLING);
        Move rookMove(7, kingRank, 5, kingRank);

        move.additionalAction = [&capture0 = position->board, rookMove] { capture0->MovePiece(rookMove); };
        pseudoLegalMoves.push_back(move);
    }

    //Queenside generation
    if(IsQueensideEmpty(color, board.pieces) && position->HasCastlingRights(color, QUEENSIDE) && GetType(board.pieces[0][kingRank]) == ROOK)
    {
        Move move(startingX, startingY, startingX - 2, startingY, CASTLING);
        Move rookMove(0, kingRank, 3, kingRank);

        move.additionalAction = [&capture0 = position->board, rookMove] { capture0->MovePiece(rookMove); };
        pseudoLegalMoves.push_back(move);
    }

    return pseudoLegalMoves;
}

vector<Move> PseudoLegalMoveGenerator::GeneratePawnMoves(int startingX, int startingY, bool generatesOnlyCaptures)
{
    vector<Move> pseudoLegalMoves;
    ChessBoard board = (*position->board);
    Color pieceColor = GetColor(board.pieces[startingX][startingY]);

    int offset = (pieceColor == ChessEngine::WHITE) ? 1 : -1;
    int startingRank = pieceColor == ChessEngine::WHITE ? 1 : 6;
    int promotionRank = (pieceColor) == ChessEngine::WHITE ? 7 : 0;
    Piece possibleSquare = board.pieces[startingX][startingY + offset];

    if(!generatesOnlyCaptures)
    {
        if(possibleSquare == EMPTY)
        {
            Move move(startingX, startingY, startingX, startingY + offset);

            if(startingY == startingRank && board.pieces[startingX][startingY + (offset * 2)] == EMPTY)
            {
                offset *= 2;
                Move move(startingX, startingY, startingX, startingY + offset);
                move.additionalAction = [this, startingX, capture0 = startingY + (offset/2)] { position->SetEnPassantSquare(startingX, capture0); };
                pseudoLegalMoves.push_back(move);
                offset /= 2;
            }

            if(move.destinationY == promotionRank)
            {
                for(int promotionType = B_PROMOTION, pieceType = BISHOP; promotionType <= Q_PROMOTION; promotionType *= 2, pieceType += 4)
                {
                    move.moveType = static_cast<MoveType>(promotionType);
                    Piece promotedPiece = static_cast<Piece>(pieceColor | pieceType);

                    move.additionalAction = [&capture0 = position->board, promotedPiece, capture1 = Square(startingX, startingY + offset)] { capture0->ReplacePiece(promotedPiece, capture1); };

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
        if((board.pieces[startingX - 1][startingY + offset] && !IsSameColor(startingX, startingY, startingX - 1, startingY + offset)) || generatesOnlyCaptures)
        {
            Move move(startingX, startingY, startingX - 1, startingY + offset);

            if(move.destinationY == promotionRank)
            {
                for(int promotionType = B_PROMOTION, pieceType = BISHOP; promotionType <= Q_PROMOTION; promotionType *= 2, pieceType += 4)
                {
                    move.moveType = static_cast<MoveType>(promotionType);
                    Piece promotedPiece = static_cast<Piece>(pieceColor | pieceType);

                    move.additionalAction = [&capture0 = position->board, promotedPiece, capture1 = Square(startingX - 1, startingY + offset)] { capture0->ReplacePiece(promotedPiece, capture1); };

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
        if((board.pieces[startingX + 1][startingY + offset] && !IsSameColor(startingX, startingY, startingX + 1, startingY + offset)) || generatesOnlyCaptures)
        {
            Move move(startingX, startingY, startingX + 1, startingY + offset);
            if(move.destinationY == promotionRank)
            {
                for(int promotionType = B_PROMOTION, pieceType = BISHOP; promotionType <= Q_PROMOTION; promotionType *= 2, pieceType += 4)
                {
                    move.moveType = static_cast<MoveType>(promotionType);
                    Piece promotedPiece = static_cast<Piece>(pieceColor | pieceType);

                    move.additionalAction = [&capture0 = position->board, promotedPiece, capture1 = Square(startingX + 1, startingY + offset)] { capture0->ReplacePiece(promotedPiece, capture1); };

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
            move.additionalAction = [&capture0 = position->board, capture1 = position->enPassantSquareX, startingY] { capture0->RemovePiece(capture1, startingY); };
            pseudoLegalMoves.push_back(move);
        }

        if(IsInBounds(startingX - 1, startingY + offset) && (startingX - 1) == position->enPassantSquareX && (startingY + offset) == (position->enPassantSquareY))
        {
            Move move(startingX, startingY, startingX - 1, startingY + offset, EN_PASSANT);
            move.additionalAction = [&capture0 = position->board, capture1 = startingX - 1, startingY] { capture0->RemovePiece(capture1, startingY); };
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
            generatedMoves = GenerateKnightMoves(startingX, startingY, ignoresEnemyKing);
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

bool
PseudoLegalMoveGenerator::DoesContainMove(std::vector<Move> generatedMoves, Move move, Move *correctMove)
{
    for(int i = 0; i < generatedMoves.size(); i++)
    {
        if(generatedMoves[i].destinationX == move.destinationX && generatedMoves[i].destinationY == move.destinationY && generatedMoves[i].startingX == move.startingX && generatedMoves[i].startingY == move.startingY)
        {
            if(IsPromotionType(move.moveType) && move.moveType != generatedMoves[i].moveType)
                continue;

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
    Square* squareList = pieceList->squares;


    for(int i = 1; i < pieceList->count; i++)
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
