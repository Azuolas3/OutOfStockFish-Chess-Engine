//
// Created by Azuolas on 7/14/2022.
//

#include "MoveGenerator.h"

namespace ChessEngine
{
    std::vector<Move> MoveGenerator::GenerateAllMoves(Color color, bool generatesThreatMap)
    {
        std::vector<Move> allGeneratedMoves;

        PieceList* pieceList = (color == WHITE) ? board->whitePieces : board->blackPieces;
        std::vector<int> xList = pieceList->squaresX;
        std::vector<int> yList = pieceList->squaresY;

        for(int i = 0; i < pieceList->squaresX.size(); i++)
        {
            int x = xList[i];
            int y = yList[i];

            std::vector<Move> generatedMoves;
            generatedMoves = GeneratePieceMoves(board->pieces[x][y], x, y, generatesThreatMap);
            allGeneratedMoves = plMoveGenerator->CombineVectors(allGeneratedMoves, generatedMoves);
        }

        return allGeneratedMoves;
    }

    std::vector<Move> MoveGenerator::GenerateAllMoves()
    {
        Color activePlayerColor = position->activePlayerColor;

        FindKingPosition(activePlayerColor);

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


    std::vector<Move> MoveGenerator::GeneratePieceMoves(ChessEngine::Piece piece, int startingX, int startingY, bool generatesThreatMap)
    {
        PieceType pieceType = GetType(piece);
        std::vector<Move> generatedMoves;
        std::vector<Move> additionalMoves;

        switch(pieceType)
        {
            case PAWN:
                generatedMoves = plMoveGenerator->GeneratePawnMoves(startingX, startingY, generatesThreatMap);
                EraseIllegalMoves(generatedMoves);
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
                additionalMoves = plMoveGenerator->GenerateCastlingMoves(startingX, startingY);
                generatedMoves = plMoveGenerator->CombineVectors(generatedMoves, additionalMoves);
                break;
        }

        return generatedMoves;
    }


    void MoveGenerator::InitThreatMaps()
    {
        memset(whiteThreatMap, false, sizeof(bool) * 8 * 8);
        memset(blackThreatMap, false, sizeof(bool) * 8 * 8);

        std::vector<Move> whiteMoves = plMoveGenerator->GenerateAllMoves(WHITE, true);
        std::vector<Move> blackMoves = plMoveGenerator->GenerateAllMoves(BLACK, true);

        for(auto & whiteMove : whiteMoves)
        {
            //whiteThreatMap[whiteMove.startingX][whiteMove.startingY] = true;
            whiteThreatMap[whiteMove.destinationX][whiteMove.destinationY] = true;
        }

        for(auto & blackMove : blackMoves)
        {
            //blackThreatMap[blackMove.startingX][blackMove.startingY] = true;
            blackThreatMap[blackMove.destinationX][blackMove.destinationY] = true;
        }
    }

    void MoveGenerator::FindKingPosition(Color color)
    {
        PieceList* pieceList = (color == WHITE) ? board->whitePieces : board->blackPieces;

        for(int i = 0; i < pieceList->count; i++)
        {
            if(GetType(board->pieces[pieceList->squaresX[i]][pieceList->squaresY[i]]) == KING)
            {
                if(color == WHITE)
                {
                    whiteKingX = pieceList->squaresX[i];
                    whiteKingY = pieceList->squaresY[i];
                }
                else
                {
                    blackKingX = pieceList->squaresX[i];
                    blackKingY = pieceList->squaresY[i];
                }
            }
        }
    }

    void MoveGenerator::GetCheckRayMap()
    {
        int kingX = whiteKingX;
        int kingY = whiteKingY;

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

        kingX = whiteKingX;
        kingY = whiteKingY;

        int attackerCount;
        std::pair<Square, Square> attackerPair = GetSquareAttackers(kingX, kingY, attackerCount);
        std::cout << attackerPair.first.x << " " << attackerPair.first.y << " " << attackerPair.second.x << " " << attackerPair.second.y << " " << attackerCount << std::endl;

        if(attackerCount > 0 && IsSlidingPiece(board->pieces[attackerPair.first.x][attackerPair.first.y]))
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

} // ChessEngine