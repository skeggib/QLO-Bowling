#include "catch.hpp"
#include "bowling.h"

TEST_CASE("Bowling API")
{
    SECTION("nominal")
    {
        bowling b;
        b.add({3, 4});
        REQUIRE(b.score() == 7);
        b.add({1, 5});
        REQUIRE(b.score() == 13);
    }

    SECTION("no negative numbers")
    {
        bowling b;
        REQUIRE_THROWS(b.add({-1, 0}));
        REQUIRE_THROWS(b.add({0, -1}));
    }

    SECTION("max 10 pairs")
    {
        bowling b;
        for (int i = 0; i < 10; ++i)
            b.add({0, 0});
        REQUIRE_THROWS(b.add({0, 0}));
    }

    SECTION("sum of a pair cannot be > 10")
    {
        bowling b;
        REQUIRE_THROWS(b.add({10, 1}));
        REQUIRE_THROWS(b.add({7, 4}));
    }

    GIVEN("the sum of a tuple is 10")
    {
        bowling b;
        b.add({ 6, 4 });

        THEN("its score is not calculated until the next value is known")
        {
            REQUIRE(b.score() == 0);
        }

        WHEN("the next value is between 1 and 9")
        {
            b.add({ 5, 4 });
            THEN("the value is added to the first tuple")
            {
                REQUIRE(b.score() == (6+4+5)+(5+4));
            }
        }
        
        WHEN("the next value is 0")
        {
            b.add({ 0, 3 });
            THEN("nothing changes")
            {
                REQUIRE(b.score() == 13);
            }
        }

        WHEN("the next value is 10")
        {
            b.add({ 10, 0 });
            THEN("the 10 is added to the first tuple but is not counted yet")
            {
                REQUIRE(b.score() == 20);
            }
        }
    }

    GIVEN("the fist value of a tuple is 10")
    {
        bowling b;
        b.add({ 10, 0 });

        THEN("the score is not counted until two new values are added")
        {
            REQUIRE(b.score() == 0);
        }

        WHEN("the sum of the next tuple is 0")
        {
            b.add({ 0, 0 });
            THEN("the score is 10")
            {
                REQUIRE(b.score() == 10);
            }
        }

        WHEN("the two next values are not 10")
        {
            b.add({ 3, 2 });
            THEN("the two values are added to the first tuple")
            {
                REQUIRE(b.score() == 20);
            }
        }

        WHEN("the next value is 10")
        {
            b.add({ 10, 0 });

            THEN("the score is not counted until the second value is added")
            {
                REQUIRE(b.score() == 0);
            }

            WHEN("a new tuple is added")
            {
                b.add({ 3, 1 });
                THEN("the second 10 is added to the first tuple, the first value is added to the first and second tuple and the second value is added to the second tuple")
                {
                    REQUIRE(b.score() == (10+10+3) + (10+3+1) + (3+1));
                }
            }
        }

        WHEN("the next tuple is a value between 1 and 9 then a 0")
        {
            b.add({ 3, 0 });
            THEN("the tuple is doubled")
            {
                REQUIRE(b.score() == 16);
            }
        }
    }

    GIVEN("the 10th tuple is a spare")
    {
        bowling b;
        for (int i = 0; i < 9; ++i)
            b.add({ 0, 0 });
        b.add({ 9, 1 });

        THEN("we allow one bonus throw")
        {
            REQUIRE_NOTHROW(b.add({ 1, 0 }));
        }

        THEN("the last throw is not doubled")
        {
            b.add({ 1, 0 });
            REQUIRE(b.score() == 11);
        }

        THEN("only one bonus throw is allowed")
        {
            REQUIRE_THROWS(b.add({ 1, 1 }));
        }
    }

    GIVEN("the 10th tuple is a strike")
    {
        bowling b;
        for (int i = 0; i < 9; ++i)
            b.add({ 0, 0 });
        b.add({ 10, 0 });

        THEN("we allow two bonus throws")
        {
            REQUIRE_NOTHROW(b.add({ 1, 1 }));
        }

        THEN("the two bonus throws are not doubled")
        {
            b.add({ 1, 1 });
            REQUIRE(b.score() == 12);
        }

        THEN("the sum of the two last throws can be greather than 10")
        {
            REQUIRE_NOTHROW(b.add({ 10, 1 }));
        }
    }

    SECTION("a perfect game a worth 300 points")
    {
        bowling b;
        for (int i = 0; i < 10; ++i)
            b.add({ 10, 0 });
        b.add({ 10, 10 });
        REQUIRE(b.score() == 300);
    }
}