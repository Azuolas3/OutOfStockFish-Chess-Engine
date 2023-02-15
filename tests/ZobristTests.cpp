#include "doctest.h"

#include "pieces.h"
#include "Move.h"
#include "FenParser.h"
#include "MoveGenerator.h"
#include "BoardUtility.h"
#include "AlgebraicNotationUtility.h"
#include "PerftUtility.h"
#include "u64.h"

TEST_CASE("Zobrist key tests")
{
    ChessEngine::FenParser fenParser;

    SUBCASE("Key remaining the same after making/unmaking moves a lot")
    {
        ChessEngine::Position* position = fenParser.loadFen(fenParser.startingFenString);
        ChessEngine::MoveGenerator* moveGenerator = new ChessEngine::MoveGenerator(position);
        u64 startingKey = position->zobristKey;
        ChessEngine::Perft(6, position, moveGenerator);
        u64 afterPerftKey = position->zobristKey;
        CHECK((startingKey == afterPerftKey));
    }
}