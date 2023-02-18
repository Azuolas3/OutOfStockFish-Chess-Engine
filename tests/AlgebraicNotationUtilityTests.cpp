#include "doctest.h"

#include "MoveGenerator/Move.h"
#include "Utilities/AlgebraicNotationUtility.h"

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

    SUBCASE("Promotion move")
    {
        Move move = Move(7, 6, 7, 7, Q_PROMOTION);

        CHECK((MoveToString(move) == "h7h8q"));
    }
}

TEST_CASE("String to move tests")
{
    SUBCASE("Diagonal move")
    {
        std::string input = "e3f4";
        Move correctMove = Move(4, 2, 5, 3);


        CHECK((StringToMove(input) == correctMove));
    }

    SUBCASE("Across board")
    {
        std::string input = "a1h8";
        Move correctMove = Move(0, 0, 7, 7);


        CHECK((StringToMove(input) == correctMove));
    }

    SUBCASE("Promotion move")
    {
        std::string input = "h7h8q";
        Move correctMove = Move(7, 6, 7, 7, Q_PROMOTION);


        CHECK((StringToMove(input) == correctMove));
    }
}
