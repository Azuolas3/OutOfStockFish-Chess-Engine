//
// Created by Azuolas on 7/6/2022.
//

#ifndef CHESS_ENGINE_PSEUDOLEGALMOVEGENERATOR_H
#define CHESS_ENGINE_PSEUDOLEGALMOVEGENERATOR_H

#include <iostream>
#include <vector>
#include "ChessBoard.h"
#include "Position.h"
#include "BoardUtility.h"
#include "Move.h"

namespace ChessEngine
{
    enum MoveGenerationType // Since we often need to slightly change move generation (generate only captures, generate for attack map, etc.)
    {
        NORMAL,
        THREAT_MAP,
        CAPTURE_ONLY
    };

    class PseudoLegalMoveGenerator
    {
        ChessEngine::Position* position;

    public:
        PseudoLegalMoveGenerator() = default;

        PseudoLegalMoveGenerator(ChessEngine::Position* position)
        {
            this-> position = position;
            //board = position.board;
        }

        void GenerateStraightMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, MoveGenerationType generationType = NORMAL);
        void GenerateDiagonalMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, MoveGenerationType generationType = NORMAL);
        void GenerateKnightMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, MoveGenerationType generationType = NORMAL);
        void GenerateKingMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, MoveGenerationType generationType = NORMAL);
        void GenerateCastlingMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY);
        void GeneratePawnMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, MoveGenerationType generationType = NORMAL);

        void GeneratePieceMoves(std::vector<Move>& pseudoLegalMoves, ChessEngine::Piece piece, int startingX, int startingY, MoveGenerationType generationType = NORMAL);
        std::vector<Move> GenerateAllMoves(ChessEngine::Color color, MoveGenerationType generationType = NORMAL);
    };
}


#endif //CHESS_ENGINE_PSEUDOLEGALMOVEGENERATOR_H
