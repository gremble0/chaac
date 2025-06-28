#include "chess_board.h"

#include <print>

int main(int, char const *const *) {
    std::println("Chaac - a chess engine");

    chess_board board;
    board.print();
    board.move(0x1UL << (1 * 8 + 3), 0x1UL << (4 * 8 + 3), player_type::WHITE);
    board.print();

    return 0;
}
