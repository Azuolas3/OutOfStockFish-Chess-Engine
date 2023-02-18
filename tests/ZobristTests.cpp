#include "doctest.h"

#include "Miscellaneous/FenParser.h"
#include "MoveGenerator/MoveGenerator.h"
#include "Utilities/PerftUtility.h"
#include "Miscellaneous/u64.h"

TEST_CASE("Zobrist key tests")
{
    ChessEngine::FenParser fenParser;

    SUBCASE("Key remaining the same after making/unmaking moves a lot")
    {
        ChessEngine::Position* position = fenParser.ParseFen(fenParser.startingFenString);
        ChessEngine::MoveGenerator* moveGenerator = new ChessEngine::MoveGenerator(position);
        u64 startingKey = position->zobristKey;
        ChessEngine::Perft(6, position, moveGenerator);
        u64 afterPerftKey = position->zobristKey;
        CHECK((startingKey == afterPerftKey));
    }
}