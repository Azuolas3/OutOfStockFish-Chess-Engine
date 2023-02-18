//
// Created by Azuolas on 7/14/2022.
//

#ifndef CHESS_ENGINE_MOVEGENERATOR_H
#define CHESS_ENGINE_MOVEGENERATOR_H

#include "PseudoLegalMoveGenerator.h"
#include "Utilities/BoardUtility.h"
#include <algorithm>
#include <iostream>

namespace ChessEngine
{
    class MoveGenerator
    {
        Position* position;
        ChessBoard* board;
        PseudoLegalMoveGenerator* plMoveGenerator;

        int whiteKingX;
        int whiteKingY;

        int blackKingX;
        int blackKingY;

        int activeKingX;
        int activeKingY;

        bool activeThreatMap[8][8];
        bool checkRayMap[8][8]; // map for squares which are in between the checked king and the sliding piece checking it (or the multiple ones)
        bool captureCheckMap[8][8]; // map for pieces checking the king

        void FindKingPosition(Color color);

        std::pair<Square, Square> GetSquareAttackers(int x, int y, int &attackerCount);
        std::vector<Square> GetAbsolutelyPinnedPieces(Color color);

        void GenerateCastlingMoves(std::vector<Move>& generatedMoves, int x, int y);

        void EraseIllegalKingMoves(std::vector<Move>& generatedMoves);
        void EraseIllegalMoves(std::vector<Move>& moveList); // Erases illegal moves for every piece except king
        void EraseIllegalEnPassantMoves(std::vector<Move>& moveList);
        void EraseIllegalPinnedMoves(std::vector<Move>& moveList, Square pinnedPiece); // Erases illegal moves for absolutely pinned pieces

        bool IsMoveEnPassant(const Move& move);
        bool IsCorrectSlidingPiece(Piece piece, int xOffset, int yOffset); // function checks if the piece can move in a certain direction (given in offsets)

        void InitThreatMaps();
        void GetCheckRayMap();
        void UpdateCaptureCheckMap(std::pair<Square, Square> attackerPair);

        void UpdateKingPositions();

    public:
        std::vector<Move> GenerateAllMoves(Color color, MoveGenerationType generationType = NORMAL); // Generates all legal moves for chosen color
        std::vector<Move> GenerateAllMoves(MoveGenerationType generationType = NORMAL); // Efficiently generates all legal moves for current active Color

        void GeneratePieceMoves(std::vector<Move>& generatedMoves, ChessEngine::Piece piece, int startingX, int startingY, MoveGenerationType generationType = NORMAL, bool isPinned = false);

        MoveGenerator(Position* position)
        {
            this->position = position;
            board = position->board;
            plMoveGenerator = new PseudoLegalMoveGenerator(position);
            FindKingPosition(WHITE);
            FindKingPosition(BLACK);
        }

        bool IsInCheck();
    };
} // ChessEngine

#endif //CHESS_ENGINE_MOVEGENERATOR_H
