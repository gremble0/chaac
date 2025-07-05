#include <catch2/catch_test_macros.hpp>

#include "notation.hh"

TEST_CASE("Converting some human readable chess positions to our internal representation") {
    SECTION("Check corners") {
        constexpr auto a1 = ch::notation::from_square({'a', 1});
        // bit 1
        STATIC_REQUIRE(a1 == 0b1);

        constexpr auto h1 = ch::notation::from_square({'h', 1});
        // bit 8
        STATIC_REQUIRE(h1 == 0b10000000);

        constexpr auto a8 = ch::notation::from_square({'a', 8});
        // bit 56 (first bit in last byte)
        STATIC_REQUIRE(a8 == 0b1'00000000'00000000'00000000'00000000'00000000'00000000'00000000);

        constexpr auto h8 = ch::notation::from_square({'h', 8});
        // bit 63 (last bit in last byte)
        STATIC_REQUIRE(h8 == 0b10000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000);
    }

    SECTION("Check some other arbitrary positions") {
        constexpr auto b3 = ch::notation::from_square({'b', 3});
        // second bit in third byte
        STATIC_REQUIRE(b3 == 0b10'00000000'00000000);

        constexpr auto d7 = ch::notation::from_square({'d', 7});
        // fourth bit in seventh byte
        STATIC_REQUIRE(d7 == 0b1000'00000000'00000000'00000000'00000000'00000000'00000000);
    }
}

TEST_CASE("Converting from internal representation to human readable chess positions") {
    SECTION("Check corners") {
        constexpr auto a1 = 0b1;
        constexpr auto a_and_1 = ch::notation::to_square(a1);
        STATIC_REQUIRE(a_and_1.first == 'a' && a_and_1.second == 1);

        constexpr auto h1 = 0b10000000;
        constexpr auto h_and_1 = ch::notation::to_square(h1);
        STATIC_REQUIRE(h_and_1.first == 'h' && h_and_1.second == 1);

        constexpr auto a8 = 0b1'00000000'00000000'00000000'00000000'00000000'00000000'00000000;
        constexpr auto a_and_8 = ch::notation::to_square(a8);
        STATIC_REQUIRE(a_and_8.first == 'a' && a_and_8.second == 8);

        constexpr auto h8 = 0b10000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000;
        constexpr auto h_and_8 = ch::notation::to_square(h8);
        STATIC_REQUIRE(h_and_8.first == 'h' && h_and_8.second == 8);
    }

    SECTION("Check some other arbitrary positions") {
        constexpr auto b3 = 0b10'00000000'00000000;
        constexpr auto b_and_3 = ch::notation::to_square(b3);
        // second bit in third byte
        STATIC_REQUIRE(b_and_3.first == 'b' && b_and_3.second == 3);

        constexpr auto d7 = 0b1000'00000000'00000000'00000000'00000000'00000000'00000000;
        constexpr auto d_and_7 = ch::notation::to_square(d7);
        // fourth bit in seventh byte
        STATIC_REQUIRE(d_and_7.first == 'd' && d_and_7.second == 7);
    }
}
