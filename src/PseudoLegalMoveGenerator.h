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

class PseudoLegalMoveGenerator
{
    ChessEngine::Position* position;
    //ChessEngine::ChessBoard* board;

    bool IsSameColor(int startingX, int startingY, int destinationX, int destinationY);

public:
    PseudoLegalMoveGenerator() = default;

    PseudoLegalMoveGenerator(ChessEngine::Position* position)
    {
        this-> position = position;
        //board = position.board;
    }

    std::vector<Move> GenerateStraightMoves(int startingX, int startingY, bool generatesThreatMap = false);
    std::vector<Move> GenerateDiagonalMoves(int startingX, int startingY, bool generatesThreatMap = false);
    std::vector<Move> GenerateKnightMoves(int startingX, int startingY, bool generatesThreatMap = false);
    std::vector<Move> GenerateKingMoves(int startingX, int startingY);
    std::vector<Move> GenerateCastlingMoves(int startingX, int startingY);
    std::vector<Move> GeneratePawnMoves(int startingX, int startingY, bool generatesOnlyCaptures = false);

    std::vector<Move> GeneratePieceMoves(ChessEngine::Piece piece, int startingX, int startingY, bool ignoresEnemyKing = false);
    std::vector<Move> GenerateAllMoves(ChessEngine::Color color, bool generatesThreatMap = false);

    std::vector<Move> CombineVectors(std::vector<Move> a, std::vector<Move> b);
    bool doesContainMove(std::vector<Move> generatedMoves, ChessEngine::Square start, ChessEngine::Square end, Move* correctMove);
};


#endif //CHESS_ENGINE_PSEUDOLEGALMOVEGENERATOR_H
