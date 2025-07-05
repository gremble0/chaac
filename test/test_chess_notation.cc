#include "notation.hh"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test converting some human readable chess positions to our internal representation") {
    SECTION("Check corners") {
        constexpr auto a1 = ch::notation::from_notation('a', 1);
        // bit 1
        REQUIRE(a1 == 0b1);

        constexpr auto h1 = ch::notation::from_notation('h', 1);
        // bit 8
        REQUIRE(h1 == 0b10000000);

        constexpr auto a8 = ch::notation::from_notation('a', 8);
        // bit 56 (first bit in last byte)
        REQUIRE(a8 == 0b1'00000000'00000000'00000000'00000000'00000000'00000000'00000000);

        constexpr auto h8 = ch::notation::from_notation('h', 8);
        // bit 63 (last bit in last byte)
        REQUIRE(h8 == 0b10000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000);
    }

    SECTION("Some other arbitrary positions") {
        constexpr auto b3 = ch::notation::from_notation('b', 3);
        // second bit in third byte
        REQUIRE(b3 == 0b10'00000000'00000000);
    }
}
