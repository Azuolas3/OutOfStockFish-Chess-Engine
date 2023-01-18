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

    void GenerateStraightMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, bool generatesThreatMap = false);
    void GenerateDiagonalMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, bool generatesThreatMap = false);
    void GenerateKnightMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, bool generatesThreatMap = false);
    void GenerateKingMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY);
    void GenerateCastlingMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY);
    void GeneratePawnMoves(std::vector<Move>& pseudoLegalMoves, int startingX, int startingY, bool generatesOnlyCaptures = false);

    void GeneratePieceMoves(std::vector<Move>& pseudoLegalMoves, ChessEngine::Piece piece, int startingX, int startingY, bool ignoresEnemyKing = false);
    std::vector<Move> GenerateAllMoves(ChessEngine::Color color, bool generatesThreatMap = false);

    std::vector<Move> CombineVectors(const std::vector<Move>& a, const std::vector<Move>& b);
    bool DoesContainMove(std::vector<Move> generatedMoves, Move move, Move *correctMove);
};


#endif //CHESS_ENGINE_PSEUDOLEGALMOVEGENERATOR_H
