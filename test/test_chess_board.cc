#include <catch2/catch_test_macros.hpp>

#include <board.hh>
#include <format>
#include <string>
#include <string_view>

// NOTE: This string contains whitespaces for each empty line as well
static constexpr std::string_view starting_presentation = R"(8 | r n b q k b n r
7 | p p p p p p p p
6 |                
5 |                
4 |                
3 |                
2 | P P P P P P P P
1 | R N B Q K B N R
  +----------------
    a b c d e f g h
)";

TEST_CASE("Test default chess board setup") {
    ch::board board;
    std::string board_presentation = std::format("{}", board);
    REQUIRE(starting_presentation == board_presentation);
}
