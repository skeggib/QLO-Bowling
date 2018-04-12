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
    }

    SECTION("the sum of a tuple is 10")
    {
        bowling b;
        b.add({ 6, 4 });

        SECTION("the next value is between 0 and 10")
        {
            b.add({ 5, 5 });
            REQUIRE(b.score() == 25);
        }
        
        SECTION("the next value is 0")
        {
            b.add({ 0, 3 });
            REQUIRE(b.score() == 13);
        }

        SECTION("the next value is 10")
        {
            b.add({ 10, 0 });
            REQUIRE(b.score() == 30);
        }
    }

    SECTION("the fist value of a tuple is 10")
    {
        bowling b;
        b.add({ 10, 0 });

        SECTION("the sum of the next tuple is 0")
        {
            b.add({ 0, 0 });
            REQUIRE(b.score() == 10);
        }

        SECTION("the next value is not 10")
        {
            b.add({ 3, 2 });
            REQUIRE(b.score() == 20);
        }

        SECTION("the next value is 10")
        {
            b.add({ 10, 0 });
            REQUIRE(b.score() == 30);
        }
    }
}