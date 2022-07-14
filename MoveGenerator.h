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
        LegalityTester legalityTester;

        bool whiteThreatMap[8][8]; // squares attacked by white pieces
        bool blackThreatMap[8][8]; // squares attacked by black pieces

        void InitThreatMaps(ChessBoard board);

    public:
        std::vector<Move> GenerateAllMoves(Color color);
        MoveGenerator(Position* position)
        {
            this->position = position;
            plMoveGenerator = new PseudoLegalMoveGenerator(position);
            InitThreatMaps(*(position->board));
        }


        PseudoLegalMoveGenerator* plMoveGenerator;
    };

} // ChessEngine

#endif //CHESS_ENGINE_MOVEGENERATOR_H
