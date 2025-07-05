#include "board.hh"
#include "input.hh"

#include <print>

int main(int /*argc*/, const char *const * /*argv*/) {
    std::println("Chaac - a chess engine");

    ch::board board;
    // TODO(gremble0): loop should finish when one player wins
    while (true) {
        std::print("{}", board);
        const auto move = ch::input::read_move(board);
        board.apply(move);
    }

    return 0;
}
