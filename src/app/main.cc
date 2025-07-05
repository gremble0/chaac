#include "board.hh"
#include "input.hh"

#include <print>

int main(int /*argc*/, const char *const * /*argv*/) {
    std::println("Chaac - a chess engine");

    ch::board board;
    // TODO(gremble0): loop should finish when one player wins
    while (true) {
        std::print("{}", board);
        ch::input::read_move(board);
    }

    return 0;
}
