//
// Created by Azuolas on 7/14/2022.
//

#ifndef CHESS_ENGINE_MOVEGENERATOR_H
#define CHESS_ENGINE_MOVEGENERATOR_H

#include "PseudoLegalMoveGenerator.h"
#include "LegalityTester.h"
#include "BoardUtility.h"
#include <algorithm>
#include <iostream>

namespace ChessEngine
{
    class MoveGenerator
    {
        Position* position;
        ChessBoard* board;
        LegalityTester legalityTester;

        //bool whiteThreatMap[8][8]; // squares attacked by white pieces
        //bool blackThreatMap[8][8];// squares attacked by black pieces

        bool isInCheck;

        int activeKingX;
        int activeKingY;

        bool activeThreatMap[8][8];

        void FindKingPosition(Color color);

        std::pair<Square, Square> GetSquareAttackers(int x, int y, int &attackerCount);
        std::vector<Square> GetAbsolutelyPinnedPieces(Color color);

        void EraseIllegalMoves(std::vector<Move>& moveList); // Erases illegal moves for every piece except king
        void EraseIllegalEnPassantMoves(std::vector<Move>& moveList);
        void EraseIllegalPinnedMoves(std::vector<Move>& moveList, Square pinnedPiece); // Erases illegal moves for absolutely pinned pieces

        bool isMoveEnPassant(const Move& move);

    public:
        std::vector<Move> GenerateAllMoves(Color color, bool generatesThreatMap = false); // Generates all legal moves for chosen color
        std::vector<Move> GenerateAllMoves(); // Efficiently generates all legal moves for current active Color


        std::vector<Move> GenerateKingMoves(int x, int y);
        std::vector<Move> GenerateCastlingMoves(int x, int y);

        std::vector<Move> GeneratePieceMoves(ChessEngine::Piece piece, int startingX, int startingY, bool generatesThreatMap = false, bool isPinned = false);

        MoveGenerator(Position* position)
        {
            this->position = position;
            board = position->board;
            plMoveGenerator = new PseudoLegalMoveGenerator(position);
            FindKingPosition(WHITE);
            FindKingPosition(BLACK);
            //InitThreatMaps();
        }


        PseudoLegalMoveGenerator* plMoveGenerator;

        void InitThreatMaps();
        void UpdateThreatMap(const Move& move);

        int whiteKingX;
        int whiteKingY;

        int blackKingX;
        int blackKingY;

        void UpdateKingPositions();

        void GetCheckRayMap();
        void UpdateCaptureCheckMap(std::pair<Square, Square> attackerPair);

        bool checkRayMap[8][8]; // map for squares which are in between the checked king and the sliding piece checking it (or the multiple ones)
        bool captureCheckMap[8][8]; // map for pieces checking the king

        bool IsInCheck();

        bool IsCorrectSlidingPiece(Piece piece, int xOffset, int yOffset); // function checks if the piece can move in a certain direction (given in offsets)
    };

} // ChessEngine

#endif //CHESS_ENGINE_MOVEGENERATOR_H
