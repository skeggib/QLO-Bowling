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

        WHEN("the next value is between 1 and 9")
        {
            b.add({ 5, 5 });
            THEN("the value is doubled")
            {
                REQUIRE(b.score() == 25);
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
            THEN("the 10 is doubled")
            {
                REQUIRE(b.score() == 30);
            }
        }
    }

    GIVEN("the fist value of a tuple is 10")
    {
        bowling b;
        b.add({ 10, 0 });

        WHEN("the sum of the next tuple is 0")
        {
            b.add({ 0, 0 });
            THEN("nothing changes")
            {
                REQUIRE(b.score() == 10);
            }
        }

        WHEN("the two next values are not 10")
        {
            b.add({ 3, 2 });
            THEN("the two values are doubled")
            {
                REQUIRE(b.score() == 20);
            }
        }

        WHEN("the next value is 10")
        {
            b.add({ 10, 0 });
            b.add({ 3, 2 });
            THEN("the 10 is doubled and the the next tuple is doubled")
            {
                REQUIRE(b.score() == 40);
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

        THEN("the 11th tuple is allowed")
        {
            REQUIRE_NOTHROW(b.add({ 0, 0 }));
        }

        WHEN("the 11th tuple is two zeros")
        {
            b.add({ 0, 0 });
            THEN("the 12th tuple is not allowed")
            {
                REQUIRE_THROWS(b.add({ 0, 0 }));
            }
        }

        WHEN("the 11th tuple is not zero, a spare nor a strike either")
        {
            b.add({ 1, 2 });
            THEN("the 12th tuple is not allowed")
            {
                REQUIRE_THROWS(b.add({ 0, 0 }));
            }
        }

        WHEN("the 11th tuple is a spare")
        {
            b.add({ 9, 1 });
            THEN("the 12th tuple is not allowed")
            {
                REQUIRE_THROWS(b.add({ 0, 0 }));
            }
        }

        WHEN("the 11th tuple is a strike")
        {
            b.add({ 10, 0 });
            THEN("the 12th tuple is not allowed")
            {
                REQUIRE_THROWS(b.add({ 0, 0 }));
            }
        }
    }
}