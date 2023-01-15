//
// Created by Azuolas on 7/14/2022.
//

#include "MoveGenerator.h"

namespace ChessEngine
{
    std::vector<Move> MoveGenerator::GenerateAllMoves(Color color, bool generatesThreatMap)
    {
        std::vector<Move> allGeneratedMoves;
        std::vector<Square> absolutelyPinnedPieces;
        //absolutelyPinnedPieces[1];

        PieceList* pieceList = (color == WHITE) ? board->whitePieces : board->blackPieces;
        Square* squareList = pieceList->squares;

        activeKingX = (color == WHITE) ? whiteKingX : blackKingX;
        activeKingY = (color == WHITE) ? whiteKingY : blackKingY;

        if(!generatesThreatMap)
            absolutelyPinnedPieces = GetAbsolutelyPinnedPieces(color);

        for(int i = 0; i < pieceList->count; i++)
        {
            int x = squareList[i].x;
            int y = squareList[i].y;

            bool isPinned = std::find(absolutelyPinnedPieces.begin(), absolutelyPinnedPieces.end(), Square(x, y)) != absolutelyPinnedPieces.end();

            std::vector<Move> generatedMoves;
            generatedMoves = GeneratePieceMoves(board->pieces[x][y], x, y, generatesThreatMap, isPinned);
            allGeneratedMoves = plMoveGenerator->CombineVectors(allGeneratedMoves, generatedMoves);
        }

        return allGeneratedMoves;
    }

    std::vector<Move> MoveGenerator::GenerateAllMoves()
    {
        InitThreatMaps();
        Color activePlayerColor = position->activePlayerColor;

        if(activePlayerColor == WHITE)
        {
            //std::copy(&whiteThreatMap[0][0], &whiteThreatMap + 8*8, &activeThreatMap[0][0]);
        }
        else
        {

        }


        FindKingPosition(activePlayerColor);

        //if active player is in check,
        if(IsInCheck())
        {
            std::pair<Square, Square> attackerPair;
            int attackerCount;

            int kingX, kingY;

            if(activePlayerColor == WHITE)
            {
                kingX = whiteKingX;
                kingY = whiteKingY;
            }
            else
            {
                kingX = blackKingX;
                kingY = blackKingY;
            }

            attackerPair = GetSquareAttackers(kingX, kingY, attackerCount);

            GetCheckRayMap();
            UpdateCaptureCheckMap(attackerPair);

            // Only calculate king moves if its a double check since its impossible for any other piece to have a legal move
            if(attackerCount == 1)
            {
                return GenerateAllMoves(activePlayerColor);
            }
            else
            {
                return GenerateKingMoves(kingX, kingY);
            }
        }
        else
        {
            return GenerateAllMoves(activePlayerColor);
        }
    }

    std::vector<Move> MoveGenerator::GenerateKingMoves(int x, int y)
    {
        std::vector<Move> generatedMoves;
        Color color = GetColor(position->board->pieces[x][y]);
        //bool threatMap[8][8] = (color == WHITE) ? blackThreatMap : whiteThreatMap;

        generatedMoves = plMoveGenerator->GenerateKingMoves(x, y);

        int moveCount = generatedMoves.size();
        for(int i = 0; i < moveCount;) // Weird iteration due to erasing moves - usual loop doesn't check every move
        {
            Move move = generatedMoves[i];
            if(color == WHITE)
            {
                if(blackThreatMap[move.destinationX][move.destinationY])
                {
                    generatedMoves.erase(generatedMoves.begin() + i);
                    moveCount--;
                }
                else
                    i++;
            }

            if(color == BLACK)
            {
                if(whiteThreatMap[move.destinationX][move.destinationY])
                {
                    generatedMoves.erase(generatedMoves.begin() + i);
                    moveCount--;
                }
                else
                    i++;
            }
        }

        return generatedMoves;
    }


    std::vector<Move> MoveGenerator::GeneratePieceMoves(ChessEngine::Piece piece, int startingX, int startingY, bool generatesThreatMap, bool isPinned)
    {
        PieceType pieceType = GetType(piece);
        std::vector<Move> generatedMoves;
        std::vector<Move> additionalMoves;

        switch(pieceType)
        {
            case PAWN:
                generatedMoves = plMoveGenerator->GeneratePawnMoves(startingX, startingY, generatesThreatMap);
                EraseIllegalMoves(generatedMoves);
                EraseIllegalEnPassantMoves(generatedMoves);
                break;

            case BISHOP:
                generatedMoves = plMoveGenerator->GenerateDiagonalMoves(startingX, startingY, generatesThreatMap);
                EraseIllegalMoves(generatedMoves);
                break;

            case KNIGHT:
                generatedMoves = plMoveGenerator->GenerateKnightMoves(startingX, startingY, generatesThreatMap);
                EraseIllegalMoves(generatedMoves);
                break;

            case ROOK:
                generatedMoves = plMoveGenerator->GenerateStraightMoves(startingX, startingY, generatesThreatMap);
                EraseIllegalMoves(generatedMoves);
                break;

            case QUEEN:
                generatedMoves = plMoveGenerator->GenerateStraightMoves(startingX, startingY, generatesThreatMap);
                additionalMoves = plMoveGenerator->GenerateDiagonalMoves(startingX, startingY, generatesThreatMap);
                generatedMoves = plMoveGenerator->CombineVectors(generatedMoves, additionalMoves);
                EraseIllegalMoves(generatedMoves);
                break;

            case KING:
                generatedMoves = GenerateKingMoves(startingX, startingY);
                additionalMoves = GenerateCastlingMoves(startingX, startingY);
                generatedMoves = plMoveGenerator->CombineVectors(generatedMoves, additionalMoves);
                break;
        }

        if(isPinned)
        {
            EraseIllegalPinnedMoves(generatedMoves, Square(startingX, startingY));
        }

        return generatedMoves;
    }


    void MoveGenerator::InitThreatMaps()
    {
        memset(whiteThreatMap, false, sizeof(bool) * 8 * 8);
        memset(blackThreatMap, false, sizeof(bool) * 8 * 8);
        memset(activeThreatMap, false, sizeof(bool) * 8 * 8);

        std::vector<Move> whiteMoves = plMoveGenerator->GenerateAllMoves(WHITE, true);
        std::vector<Move> blackMoves = plMoveGenerator->GenerateAllMoves(BLACK, true);

        for(auto & whiteMove : whiteMoves)
        {
            //whiteThreatMap[whiteMove.startingX][whiteMove.startingY] = true;
            whiteThreatMap[whiteMove.destinationX][whiteMove.destinationY] = true;
            if(position->activePlayerColor == BLACK)
            {
                activeThreatMap[whiteMove.destinationX][whiteMove.destinationY] = true;
            }
        }

        for(auto & blackMove : blackMoves)
        {
            //blackThreatMap[blackMove.startingX][blackMove.startingY] = true;
            blackThreatMap[blackMove.destinationX][blackMove.destinationY] = true;
            if(position->activePlayerColor == WHITE)
            {
                activeThreatMap[blackMove.destinationX][blackMove.destinationY] = true;
            }
        }
    }

    void MoveGenerator::FindKingPosition(Color color)
    {
        PieceList* pieceList = (color == WHITE) ? board->whitePieces : board->blackPieces;

        for(int i = 0; i < pieceList->count; i++)
        {
            if(GetType(board->pieces[pieceList->squares[i].x][pieceList->squares[i].y]) == KING)
            {
                if(color == WHITE)
                {
                    whiteKingX = pieceList->squares[i].x;
                    whiteKingY = pieceList->squares[i].y;
                }
                else
                {
                    blackKingX = pieceList->squares[i].x;
                    blackKingY = pieceList->squares[i].y;
                }
            }
        }
    }

    void MoveGenerator::GetCheckRayMap()
    {
        int kingX;
        int kingY;

        memset(checkRayMap, false, sizeof(bool) * 8 * 8);

        if(position->activePlayerColor == WHITE)
        {
            kingX = whiteKingX;
            kingY = whiteKingY;
        }
        else
        {
            kingX = blackKingX;
            kingY = blackKingY;
        }

        int attackerCount;
        std::pair<Square, Square> attackerPair = GetSquareAttackers(kingX, kingY, attackerCount);
        //std::cout << attackerPair.first.x << " " << attackerPair.first.y << " " << attackerPair.second.x << " " << attackerPair.second.y << " " << attackerCount << std::endl;

        if(attackerCount > 0 && IsSlidingPiece(board->pieces[attackerPair.first.x][attackerPair.first.y])) // probably a bug here - should cast for both pieces(attackers)
            CastRayToSquare(std::ref(checkRayMap), Square(kingX, kingY), attackerPair.first);
    }

    std::pair<Square, Square> MoveGenerator::GetSquareAttackers(int x, int y, int &attackerCount)
    {
        std::vector<Move> generatedMoves = plMoveGenerator->GenerateKnightMoves(x, y);

        Square attackers[2] = {Square(-1, -1), Square(-1, -1)};
        attackerCount = 0;


        for(Move& move : generatedMoves)
        {
            Piece piece = board->pieces[move.destinationX][move.destinationY];
            if(GetType(piece) == KNIGHT && GetColor(piece) != position->activePlayerColor)
            {
                attackers[attackerCount] = Square(move.destinationX, move.destinationY);
                attackerCount++;
                break;
            }
        }


        generatedMoves = plMoveGenerator->GenerateStraightMoves(x, y);

        for(Move& move : generatedMoves)
        {
            Piece piece = board->pieces[move.destinationX][move.destinationY];
            if(IsRookOrQueen(piece) && GetColor(piece) != position->activePlayerColor)
            {
                attackers[attackerCount] = Square(move.destinationX, move.destinationY);
                attackerCount++;
                break;
            }
        }


        if(attackerCount == 2)
            return std::pair<Square, Square>(attackers[0], attackers[1]);

        generatedMoves = plMoveGenerator->GenerateDiagonalMoves(x, y);

        for(Move& move : generatedMoves)
        {
            Piece piece = board->pieces[move.destinationX][move.destinationY];
            if(IsBishopOrQueen(piece) && GetColor(piece) != position->activePlayerColor)
            {
                attackers[attackerCount] = Square(move.destinationX, move.destinationY);
                attackerCount++;
                break;
            }
        }

        if(attackerCount == 2)
            return std::pair<Square, Square>(attackers[0], attackers[1]);

        generatedMoves = plMoveGenerator->GeneratePawnMoves(x, y, true);

        for(Move& move : generatedMoves)
        {
            Piece piece = board->pieces[move.destinationX][move.destinationY];
            if(GetType(piece) == PAWN && GetColor(piece) != position->activePlayerColor)
            {
                attackers[attackerCount] = Square(move.destinationX, move.destinationY);
                attackerCount++;
                break;
            }
        }

        return std::pair<Square, Square>(attackers[0], attackers[1]);
    }

    bool MoveGenerator::IsInCheck()
    {
        if(position->activePlayerColor == WHITE)
        {
            if(blackThreatMap[whiteKingX][whiteKingY])
                return true;
        }
        else
        {
            if(whiteThreatMap[blackKingX][blackKingY])
                return true;
        }

        return false;
    }

    void MoveGenerator::EraseIllegalMoves(std::vector<Move>& moveList)
    {
        if(!IsInCheck())
            return;

        int moveCount = moveList.size();
        for(int i = 0; i < moveCount;)
        {
            Move move = moveList[i];

            if(!captureCheckMap[move.destinationX][move.destinationY] && !checkRayMap[move.destinationX][move.destinationY])
            {
                if(isMoveEnPassant(move)) // cover for edge case where move square doesn't coincide with capture square - en passant
                {
                    int offset = (position->activePlayerColor == WHITE) ? -1 : 1;
                    if(captureCheckMap[move.destinationX][move.destinationY + offset])
                    {
                        i++;
                        continue;
                    }
                }

                moveList.erase(moveList.begin() + i);
                moveCount--;
            }
            else
                i++;
        }
    }

    void MoveGenerator::EraseIllegalPinnedMoves(std::vector<Move> &moveList, Square pinnedPiece)
    {
        Square direction = Square(pinnedPiece.x - activeKingX, pinnedPiece.y - activeKingY);
        direction = NormalizeVector(direction);

        bool pinnedRay[8][8];
        memset(pinnedRay, false, sizeof(bool) * 8 * 8);
        CastRayInDirection(pinnedRay, Square(activeKingX, activeKingY), direction);

        int moveCount = moveList.size();
        for(int i = 0; i < moveCount;)
        {
            Move move = moveList[i];
            if(!pinnedRay[move.destinationX][move.destinationY])
            {
                moveList.erase(moveList.begin() + i);
                moveCount--;
            }
            else
                i++;
        }
    }

    void MoveGenerator::UpdateCaptureCheckMap(std::pair<Square, Square> attackerPair)
    {
        memset(captureCheckMap, false, sizeof(bool) * 8 * 8);

        if(attackerPair.first.x != -1)
        {
            captureCheckMap[attackerPair.first.x][attackerPair.first.y] = true;
            if(attackerPair.second.x != -1)
                captureCheckMap[attackerPair.second.x][attackerPair.second.y] = true;
        }
    }

    bool MoveGenerator::isMoveEnPassant(Move move)
    {
        if(move.moveType == EN_PASSANT)
            return true;
        else
            return false;
    }

    std::vector<Move> MoveGenerator::GenerateCastlingMoves(int startingX, int startingY)
    {

        std::vector<Move> pseudoLegalMoves;

        int kingRank = startingY;
        Color color = GetColor(board->pieces[startingX][startingY]);

        if(IsInCheck())
            return pseudoLegalMoves;


        //Kingside generation
        if(IsKingsideEmpty(color, board->pieces) && position->HasCastlingRights(color, KINGSIDE) && GetType(board->pieces[7][kingRank]) == ROOK
        && !activeThreatMap[5][kingRank] && !activeThreatMap[6][kingRank]) // checking only for type because color doesn't matter - all castling conditions cant be met if the rook is of opposite color.
        {
            Move move(startingX, startingY, startingX + 2, startingY, CASTLING);
            Move rookMove(7, kingRank, 5, kingRank);

            move.additionalAction = std::bind(&ChessBoard::MovePiece, std::ref(position->board), rookMove);
            pseudoLegalMoves.push_back(move);
        }

        //Queenside generation
        if(IsQueensideEmpty(color, board->pieces) && position->HasCastlingRights(color, QUEENSIDE) && GetType(board->pieces[0][kingRank]) == ROOK
        && !activeThreatMap[3][kingRank] && !activeThreatMap[2][kingRank])
        {
            Move move(startingX, startingY, startingX - 2, startingY, CASTLING);
            Move rookMove(0, kingRank, 3, kingRank);

            move.additionalAction = std::bind(&ChessBoard::MovePiece, std::ref(position->board), rookMove);
            pseudoLegalMoves.push_back(move);
        }
    }

    std::vector<Square> MoveGenerator::GetAbsolutelyPinnedPieces(Color color)
    {
        int kingX = (color == WHITE) ? whiteKingX : blackKingX;
        int kingY = (color == WHITE) ? whiteKingY : blackKingY;

        std::vector<Square> pinnedPieces;

        for(int currentDir = 0; currentDir < 8; currentDir++)
        {
            Square pinnedPiece{};

            for(int x = kingX + xDirOffset[currentDir], y = kingY + yDirOffset[currentDir]; ;x += xDirOffset[currentDir], y += yDirOffset[currentDir])
            {
                if(!IsInBounds(x, y))
                    break;

                if(board->pieces[x][y] != EMPTY)
                {
                    if(GetColor(board->pieces[x][y]) == position->activePlayerColor)
                    {
                        pinnedPiece = Square(x, y);

                        x += xDirOffset[currentDir];
                        y += yDirOffset[currentDir];

                        bool haveFoundPinner = false;
                        while(!haveFoundPinner && IsInBounds(x, y))
                        {
                            if(board->pieces[x][y] != EMPTY)
                            {
                                if(GetColor(board->pieces[x][y]) != position->activePlayerColor && IsCorrectSlidingPiece(board->pieces[x][y], xDirOffset[currentDir], yDirOffset[currentDir]))
                                {
                                    //pinnerPiece = Square(x, y);
                                    haveFoundPinner = true;
                                    pinnedPieces.push_back(pinnedPiece);
                                }
                                else
                                    break;
                            }

                            x += xDirOffset[currentDir];
                            y += yDirOffset[currentDir];
                        }
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        return pinnedPieces;
    }

    bool MoveGenerator::IsCorrectSlidingPiece(Piece piece, int xOffset, int yOffset) // function for checking if the sliding piece can move in given direction (given in offset)
    {
        if((xOffset == 0 || yOffset == 0) && IsRookOrQueen(piece))
            return true;
        if((xOffset != 0 && yOffset != 0) && IsBishopOrQueen(piece))
            return true;

        return false;
    }

    void MoveGenerator::EraseIllegalEnPassantMoves(std::vector<Move> &moveList)
    {
        int moveCount = moveList.size();
        for(int i = 0; i < moveCount;) {
            Move move = moveList[i];

            if (!isMoveEnPassant(move))
            {
                i++;
                continue;
            }
            else // cover for edge case where en passant causes discovered check by moving 2 pieces from same rank
            {
                if (move.startingY == activeKingY)
                {
                    int offset = (activeKingX - move.startingX > 0) ? -1 : 1; // find direction from king towards en passant square

                    for (int x = activeKingX + offset; IsInBounds(x,activeKingY); x+= offset) // go through each square in that direction
                    {
                        if (board->pieces[x][activeKingY] != EMPTY)
                        {
                            if (GetType(board->pieces[x][activeKingY]) == PAWN && (x == move.destinationX || move.startingX == x)) // if its the captured pawn or en passant pawn, continue
                            {
                                continue;
                            }
                            else if (IsCorrectSlidingPiece(board->pieces[x][activeKingY], -offset,0)) //if you have found a piece which can move in that direction, erase
                            {
                                moveList.erase(moveList.begin() + i);
                                moveCount--;
                                break;
                            }
                            else // else, that's a different piece and no pins are happening
                            {
                                i++;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    i++;
                    continue;
                }
            }
        }
    }

} // ChessEngine