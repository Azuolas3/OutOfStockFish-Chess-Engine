#include "doctest.h"

#include "pieces.h"
#include "Move.h"
#include "FenParser.h"
#include "MoveGenerator.h"
#include "BoardUtility.h"
#include "AlgebraicNotationUtility.h"
#include "PerftUtility.h"
#include "u64.h"

TEST_CASE("Perft Results")
{
    ChessEngine::FenParser fenParser;
    u64 nodes;

    SUBCASE("Starting Position")
    {
        ChessEngine::Position* position = fenParser.loadFen(fenParser.startingFenString);
        ChessEngine::MoveGenerator* moveGenerator = new ChessEngine::MoveGenerator(position);
        nodes = ChessEngine::Perft(6, position, moveGenerator);
        CHECK((nodes == 119060324));
    }

    SUBCASE("Kiwipete (trickier) Position")
    {
        ChessEngine::Position* position = fenParser.loadFen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
        ChessEngine::MoveGenerator* moveGenerator = new ChessEngine::MoveGenerator(position);

        nodes = ChessEngine::Perft(5, position, moveGenerator);
        CHECK((nodes == 193690690));
    }

    SUBCASE("Tricky En Passant Position")
    {
        ChessEngine::Position* position = fenParser.loadFen("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
        ChessEngine::MoveGenerator* moveGenerator = new ChessEngine::MoveGenerator(position);

        nodes = ChessEngine::Perft(5, position, moveGenerator);
        CHECK((nodes == 674624));
    }
}