#include "notation.hh"
#include <catch2/catch_test_macros.hpp>
#include <cstdint>

TEST_CASE("Test converting some human readable chess positions to our internal representation") {
    constexpr uint64_t a1 = ch::notation::from_notation('a', 1);
    REQUIRE(a1 == 0b1000000000000000000000000000000000000000000000000000000000000000);
}
