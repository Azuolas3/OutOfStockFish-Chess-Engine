#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "pieces.h"

TEST_CASE("Piece Construction")
{
    ChessEngine::Color pieceColor = ChessEngine::WHITE;
    ChessEngine::PieceType pieceType = ChessEngine::ROOK;

    ChessEngine::Piece piece = static_cast<ChessEngine::Piece>(pieceColor | pieceType);
    CHECK((piece == ChessEngine::W_ROOK));
}