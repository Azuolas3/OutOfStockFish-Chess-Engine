//
// Created by Azuolas on 7/14/2022.
//

#ifndef CHESS_ENGINE_MOVEGENERATOR_H
#define CHESS_ENGINE_MOVEGENERATOR_H

#include "PseudoLegalMoveGenerator.h"
#include "LegalityTester.h"

namespace ChessEngine
{
    class MoveGenerator
    {
        Position* position;
        ChessBoard* board;
        LegalityTester legalityTester;

        bool whiteThreatMap[8][8]; // squares attacked by white pieces
        // squares attacked by black pieces

        bool isInCheck;

        int activeKingX;
        int activeKingY;

        void FindKingPosition(Color color);
        std::pair<Square, Square> GetSquareAttackers(int x, int y, int &attackerCount);

        void EraseIllegalMoves(std::vector<Move>& moveList); // Erases illegal moves for every piece except king

    public:
        std::vector<Move> GenerateAllMoves(Color color, bool generatesThreatMap = false); // Generates all legal moves for chosen color
        std::vector<Move> GenerateAllMoves(); // Efficiently generates all legal moves for current active Color


        std::vector<Move> GenerateKingMoves(int x, int y);

        std::vector<Move> GeneratePieceMoves(ChessEngine::Piece piece, int startingX, int startingY, bool generatesThreatMap = false);

        MoveGenerator(Position* position)
        {
            this->position = position;
            board = position->board;
            plMoveGenerator = new PseudoLegalMoveGenerator(position);
            FindKingPosition(WHITE);
            FindKingPosition(BLACK);
            InitThreatMaps();
        }


        PseudoLegalMoveGenerator* plMoveGenerator;

        void InitThreatMaps();

        int whiteKingX;
        int whiteKingY;

        int blackKingX;
        int blackKingY;

        void GetCheckRayMap();
        void UpdateCaptureCheckMap(std::pair<Square, Square> attackerPair);

        bool checkRayMap[8][8];
        bool captureCheckMap[8][8];

        bool IsInCheck();

        bool blackThreatMap[8][8];
    };

} // ChessEngine

#endif //CHESS_ENGINE_MOVEGENERATOR_H
