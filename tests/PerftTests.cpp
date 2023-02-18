#include "doctest.h"

#include "Miscellaneous/FenParser.h"
#include "MoveGenerator/MoveGenerator.h"
#include "Utilities/PerftUtility.h"
#include "Miscellaneous/u64.h"

TEST_CASE("Perft Results")
{
    ChessEngine::FenParser fenParser;
    u64 nodes;

    SUBCASE("Starting Position")
    {
        ChessEngine::Position* position = fenParser.ParseFen(fenParser.startingFenString);
        ChessEngine::MoveGenerator* moveGenerator = new ChessEngine::MoveGenerator(position);
        nodes = ChessEngine::Perft(6, position, moveGenerator);
        CHECK((nodes == 119060324));
    }

    SUBCASE("Kiwipete (trickier) Position")
    {
        ChessEngine::Position* position = fenParser.ParseFen(
                "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
        ChessEngine::MoveGenerator* moveGenerator = new ChessEngine::MoveGenerator(position);

        nodes = ChessEngine::Perft(5, position, moveGenerator);
        CHECK((nodes == 193690690));
    }

    SUBCASE("Tricky En Passant Position")
    {
        ChessEngine::Position* position = fenParser.ParseFen("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
        ChessEngine::MoveGenerator* moveGenerator = new ChessEngine::MoveGenerator(position);

        nodes = ChessEngine::Perft(5, position, moveGenerator);
        CHECK((nodes == 674624));
    }
}