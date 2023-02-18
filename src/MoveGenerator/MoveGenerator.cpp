//
// Created by Azuolas on 7/14/2022.
//

#include "MoveGenerator.h"

namespace ChessEngine
{
    std::vector<Move> MoveGenerator::GenerateAllMoves(Color color, MoveGenerationType generationType)
    {
        int maxSize = 256; // maximum theoretical number of moves is 218, 256 just in case and since it's a beautiful number :)

        std::vector<Move> generatedMoves;
        generatedMoves.reserve(maxSize);

        std::vector<Square> absolutelyPinnedPieces;

        PieceList *pieceList = (color == WHITE) ? board->whitePieces : board->blackPieces;
        Square *squareList = pieceList->squares;

        absolutelyPinnedPieces = GetAbsolutelyPinnedPieces(color);

        for (int i = 1; i < pieceList->count; i++)
        {
            int x = squareList[i].x;
            int y = squareList[i].y;

            bool isPinned = std::find(absolutelyPinnedPieces.begin(), absolutelyPinnedPieces.end(), Square(x, y)) != absolutelyPinnedPieces.end();

            GeneratePieceMoves(generatedMoves, board->pieces[x][y], x, y, generationType, isPinned);
        }

        return generatedMoves;
    }

    std::vector<Move> MoveGenerator::GenerateAllMoves(MoveGenerationType generationType)
    {
        Color activePlayerColor = position->activePlayerColor;
        UpdateKingPositions();

        activeKingX = (activePlayerColor == WHITE) ? whiteKingX : blackKingX;
        activeKingY = (activePlayerColor == WHITE) ? whiteKingY : blackKingY;

        InitThreatMaps();

        //if active player is in check, get necessary info before generating moves
        if (IsInCheck())
        {
            std::pair<Square, Square> attackerPair;
            int attackerCount;

            int kingX, kingY;

            if (activePlayerColor == WHITE)
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

            // Only calculate king moves if it's a double check since its impossible for any other piece to have a legal move
            if (attackerCount == 1)
            {
                return GenerateAllMoves(activePlayerColor, generationType);
            }
            else
            {
                std::vector<Move> kingMoves;
                plMoveGenerator->GenerateKingMoves(kingMoves, kingX, kingY);
                EraseIllegalKingMoves(kingMoves);
                return kingMoves;
            }
        }
        else
        {
            return GenerateAllMoves(activePlayerColor, generationType);
        }
    }

    void MoveGenerator::GeneratePieceMoves(std::vector<Move> &generatedMoves, ChessEngine::Piece piece, int startingX,
                                           int startingY, MoveGenerationType generationType, bool isPinned)
    {
        PieceType pieceType = GetType(piece);

        switch (pieceType)
        {
            case PAWN:
                plMoveGenerator->GeneratePawnMoves(generatedMoves, startingX, startingY, generationType);
                EraseIllegalMoves(generatedMoves);
                EraseIllegalEnPassantMoves(generatedMoves);
                break;

            case BISHOP:
                plMoveGenerator->GenerateDiagonalMoves(generatedMoves, startingX, startingY, generationType);
                EraseIllegalMoves(generatedMoves);
                break;

            case KNIGHT:
                plMoveGenerator->GenerateKnightMoves(generatedMoves, startingX, startingY, generationType);
                EraseIllegalMoves(generatedMoves);
                break;

            case ROOK:
                plMoveGenerator->GenerateStraightMoves(generatedMoves, startingX, startingY, generationType);
                EraseIllegalMoves(generatedMoves);
                break;

            case QUEEN:
                plMoveGenerator->GenerateStraightMoves(generatedMoves, startingX, startingY, generationType);
                plMoveGenerator->GenerateDiagonalMoves(generatedMoves, startingX, startingY, generationType);
                EraseIllegalMoves(generatedMoves);
                break;

            case KING:
                plMoveGenerator->GenerateKingMoves(generatedMoves, startingX, startingY, generationType);
                EraseIllegalKingMoves(generatedMoves);
                if (generationType == NORMAL)
                    GenerateCastlingMoves(generatedMoves, startingX, startingY);
                break;
        }

        if (isPinned)
        {
            EraseIllegalPinnedMoves(generatedMoves, Square(startingX, startingY));
        }
    }


    void MoveGenerator::InitThreatMaps()
    {
        memset(activeThreatMap, false, sizeof(bool) * 8 * 8);

        std::vector<Move> opponentMoves = plMoveGenerator->GenerateAllMoves(GetOppositeColor(position->activePlayerColor), THREAT_MAP);

        for (auto &move: opponentMoves)
        {
            activeThreatMap[move.destinationX][move.destinationY] = true;
        }
    }

    void MoveGenerator::FindKingPosition(Color color)
    {
        PieceList *pieceList = (color == WHITE) ? board->whitePieces : board->blackPieces;

        for (int i = 0; i < pieceList->count; i++)
        {
            if (GetType(board->pieces[pieceList->squares[i].x][pieceList->squares[i].y]) == KING)
            {
                if (color == WHITE)
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

        if (position->activePlayerColor == WHITE)
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

        if (attackerCount > 0 && IsSlidingPiece(board->pieces[attackerPair.first.x][attackerPair.first.y]))
        {
            CastRayToSquare(std::ref(checkRayMap), Square(kingX, kingY), attackerPair.first);
        }
        if (attackerCount > 1 && IsSlidingPiece(board->pieces[attackerPair.second.x][attackerPair.second.y]))
        {
            CastRayToSquare(std::ref(checkRayMap), Square(kingX, kingY), attackerPair.second);
        }
    }

    std::pair<Square, Square> MoveGenerator::GetSquareAttackers(int x, int y, int &attackerCount)
    {
        std::vector<Move> generatedMoves;
        plMoveGenerator->GenerateKnightMoves(generatedMoves, x, y);

        Square attackers[2] = {Square(-1, -1), Square(-1, -1)};
        attackerCount = 0;


        for (Move &move: generatedMoves)
        {
            Piece piece = board->pieces[move.destinationX][move.destinationY];
            if (GetType(piece) == KNIGHT && GetColor(piece) != position->activePlayerColor)
            {
                attackers[attackerCount] = Square(move.destinationX, move.destinationY);
                attackerCount++;
                break;
            }
        }

        generatedMoves.clear();
        plMoveGenerator->GenerateStraightMoves(generatedMoves, x, y);

        for (Move &move: generatedMoves)
        {
            Piece piece = board->pieces[move.destinationX][move.destinationY];
            if (IsRookOrQueen(piece) && GetColor(piece) != position->activePlayerColor)
            {
                attackers[attackerCount] = Square(move.destinationX, move.destinationY);
                attackerCount++;
                break;
            }
        }


        if (attackerCount == 2)
            return std::pair<Square, Square>(attackers[0], attackers[1]);

        generatedMoves.clear();
        plMoveGenerator->GenerateDiagonalMoves(generatedMoves, x, y);

        for (Move &move: generatedMoves)
        {
            Piece piece = board->pieces[move.destinationX][move.destinationY];
            if (IsBishopOrQueen(piece) && GetColor(piece) != position->activePlayerColor) {
                attackers[attackerCount] = Square(move.destinationX, move.destinationY);
                attackerCount++;
                break;
            }
        }

        if (attackerCount == 2)
            return std::pair<Square, Square>(attackers[0], attackers[1]);

        generatedMoves.clear();
        plMoveGenerator->GeneratePawnMoves(generatedMoves, x, y, THREAT_MAP);

        for (Move &move: generatedMoves)
        {
            Piece piece = board->pieces[move.destinationX][move.destinationY];
            if (GetType(piece) == PAWN && GetColor(piece) != position->activePlayerColor)
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
        if (activeThreatMap[activeKingX][activeKingY])
            return true;

        return false;
    }

    void MoveGenerator::EraseIllegalMoves(std::vector<Move> &moveList)
    {
        if (!IsInCheck())
            return;

        int moveCount = moveList.size();
        for (int i = moveCount - 1; i >= 0; i--)
        {
            Move move = moveList[i];
            Piece currentPiece = board->pieces[move.startingX][move.startingY];

            if (IsKing(currentPiece))
            {
                break;
            }
            if (!captureCheckMap[move.destinationX][move.destinationY] &&
                !checkRayMap[move.destinationX][move.destinationY]) {
                if (IsMoveEnPassant(move)) // cover for edge case where move square doesn't coincide with capture square - en passant
                {
                    int offset = (position->activePlayerColor == WHITE) ? -1 : 1;
                    if (captureCheckMap[move.destinationX][move.destinationY + offset]) {
                        continue;
                    }
                }

                moveList.erase(moveList.begin() + i);
            }
        }
    }

    void MoveGenerator::EraseIllegalKingMoves(std::vector<Move> &generatedMoves)
    {
        int moveCount = generatedMoves.size();
        for (int i = moveCount - 1; i >= 0; i--) {
            Move move = generatedMoves[i];
            Piece currentPiece = board->pieces[move.startingX][move.startingY];

            if (!IsKing(currentPiece))
            {
                break;
            }
            if (activeThreatMap[move.destinationX][move.destinationY])
            {
                generatedMoves.erase(generatedMoves.begin() + i);
                moveCount--;
            }
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
        for (int i = moveCount - 1; i >= 0; i--) {
            Move move = moveList[i];
            if (move.startingX != pinnedPiece.x || move.startingY != pinnedPiece.y) {
                break;
            }
            if (!pinnedRay[move.destinationX][move.destinationY])
            {
                moveList.erase(moveList.begin() + i);
            }
        }
    }

    void MoveGenerator::EraseIllegalEnPassantMoves(std::vector<Move> &moveList)
    {
        int moveNumber = moveList.size() - 1;
        if (moveList.empty())
            return;

        Move move = moveList[moveNumber];
        Piece activePiece = board->pieces[move.startingX][move.startingY];
        Color activeColor = GetColor(activePiece);

        if (!IsMoveEnPassant(move))
        {
            return;
        }
        else // cover for edge case where en passant causes discovered check by moving 2 pieces from same rank
        {
            if (move.startingY == activeKingY)
            {
                int offset = (activeKingX - move.startingX > 0) ? -1 : 1; // find direction from king towards en passant square

                for (int x = activeKingX + offset;; x += offset) // go through each square in that direction
                {
                    if (!IsInBounds(x, activeKingY))
                    {
                        break;
                    }

                    if (board->pieces[x][activeKingY] != EMPTY)
                    {
                        if (GetType(board->pieces[x][activeKingY]) == PAWN && (x == move.destinationX || move.startingX == x)) // if its the captured pawn or en passant pawn, continue
                        {
                            continue;
                        }
                        else if (IsCorrectSlidingPiece(board->pieces[x][activeKingY], -offset, 0) && GetColor(board->pieces[x][activeKingY]) != activeColor) //if you have found a piece which can move in that direction, erase
                        {
                            moveList.erase(moveList.begin() + moveNumber);
                            break;
                        }
                        else // else, that's a different piece and no pins are happening
                        {
                            break;
                        }
                    }
                }
            }
        }
    }

    void MoveGenerator::UpdateCaptureCheckMap(std::pair<Square, Square> attackerPair)
    {
        memset(captureCheckMap, false, sizeof(bool) * 8 * 8);

        if (attackerPair.first.x != -1)
        {
            captureCheckMap[attackerPair.first.x][attackerPair.first.y] = true;
            if (attackerPair.second.x != -1)
                captureCheckMap[attackerPair.second.x][attackerPair.second.y] = true;
        }
    }

    bool MoveGenerator::IsMoveEnPassant(const Move &move)
    {
        if (move.moveType == EN_PASSANT)
            return true;
        else
            return false;
    }

    void MoveGenerator::GenerateCastlingMoves(std::vector<Move> &generatedMoves, int startingX, int startingY)
    {
        int kingRank = startingY;
        Color color = GetColor(board->pieces[startingX][startingY]);


        if (IsInCheck())
            return;

        //Kingside generation
        if (IsKingsideEmpty(color, board->pieces) && position->HasCastlingRights(color, KINGSIDE) &&
            GetType(board->pieces[7][kingRank]) == ROOK // checking only for type because color doesn't matter - all castling conditions cant be met if the rook is of opposite color.
            && !activeThreatMap[5][kingRank] &&
            !activeThreatMap[6][kingRank])
        {

            Move move(startingX, startingY, startingX + 2, startingY, CASTLING);
            generatedMoves.push_back(move);
        }

        //Queenside generation
        if (IsQueensideEmpty(color, board->pieces) && position->HasCastlingRights(color, QUEENSIDE) &&
            GetType(board->pieces[0][kingRank]) == ROOK
            && !activeThreatMap[3][kingRank] && !activeThreatMap[2][kingRank])
        {
            Move move(startingX, startingY, startingX - 2, startingY, CASTLING);
            generatedMoves.push_back(move);
        }
    }

    std::vector<Square> MoveGenerator::GetAbsolutelyPinnedPieces(Color color)
    {
        int kingX = (color == WHITE) ? whiteKingX : blackKingX;
        int kingY = (color == WHITE) ? whiteKingY : blackKingY;

        std::vector<Square> pinnedPieces;

        for (int currentDir = 0; currentDir < 8; currentDir++) {
            Square pinnedPiece{};

            for (int x = kingX + xDirOffset[currentDir], y = kingY + yDirOffset[currentDir];; x += xDirOffset[currentDir], y += yDirOffset[currentDir])
            {
                if (!IsInBounds(x, y))
                    break;

                if (board->pieces[x][y] != EMPTY)
                {
                    if (GetColor(board->pieces[x][y]) == position->activePlayerColor)
                    {
                        pinnedPiece = Square(x, y);

                        x += xDirOffset[currentDir];
                        y += yDirOffset[currentDir];

                        bool haveFoundPinner = false;
                        while (!haveFoundPinner && IsInBounds(x, y))
                        {
                            if (board->pieces[x][y] != EMPTY)
                            {
                                if (GetColor(board->pieces[x][y]) != position->activePlayerColor &&
                                    IsCorrectSlidingPiece(board->pieces[x][y], xDirOffset[currentDir],yDirOffset[currentDir])) {
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
        if ((xOffset == 0 || yOffset == 0) && IsRookOrQueen(piece))
            return true;
        if ((xOffset != 0 && yOffset != 0) && IsBishopOrQueen(piece))
            return true;

        return false;
    }

    void MoveGenerator::UpdateKingPositions()
    {
        whiteKingX = board->whiteKingX;
        whiteKingY = board->whiteKingY;

        blackKingX = board->blackKingX;
        blackKingY = board->blackKingY;
    }
}