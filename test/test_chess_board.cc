#include <catch2/catch_test_macros.hpp>

#include <board.hh>
#include <format>
#include <string>
#include <string_view>

// NOTE: This string contains whitespaces for each empty line as well
static constexpr std::string_view starting_presentation = R"(r n b k q b n r
p p p p p p p p
               
               
               
               
P P P P P P P P
R N B K Q B N R
)";

TEST_CASE("Test default chess board setup") {
    ch::board board;
    std::string board_presentation = std::format("{}", board);
    REQUIRE(starting_presentation == board_presentation);
}
