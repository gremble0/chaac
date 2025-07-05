#include <catch2/catch_test_macros.hpp>

#include <board.hh>
#include <format>
#include <string>
#include <string_view>

// NOTE: This string contains whitespaces for each empty line as well
static constexpr std::string_view starting_presentation = R"(R N B K Q B N R
P P P P P P P P
               
               
               
               
p p p p p p p p
r n b k q b n r
)";

TEST_CASE("Test default chess board setup") {
    ch::board board;
    std::string board_presentation = std::format("{}", board);
    REQUIRE(starting_presentation == board_presentation);
}
