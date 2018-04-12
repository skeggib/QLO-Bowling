#include "catch.hpp"
#include "api.h"

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

    SECTION("max 10 values")
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
}