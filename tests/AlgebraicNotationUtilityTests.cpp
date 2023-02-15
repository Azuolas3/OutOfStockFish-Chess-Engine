#include "doctest.h"

#include "Move.h"
#include "AlgebraicNotationUtility.h"

TEST_CASE("Move to string tests")
{
    SUBCASE("Diagonal move")
    {
        Move move = Move(4, 2, 5, 3);

        CHECK((MoveToString(move) == "e3f4"));
    }

    SUBCASE("Across board")
    {
        Move move = Move(0, 0, 7, 7);

        CHECK((MoveToString(move) == "a1h8"));
    }
}
