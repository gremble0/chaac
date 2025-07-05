#include <catch2/catch_test_macros.hpp>

#include "board.hh"

static constexpr std::string_view a2_to_a3 = R"(R N B K Q B N R
P P P P P P P P
               
               
               
p              
  p p p p p p p
r n b k q b n r
)";

TEST_CASE("Test move pawn") {
    // ch::chess_board board;
    // std::string board_presentation = std::format("{}", board);
    // board.apply({});
    // REQUIRE(a2_to_a3 == board_presentation);
}
