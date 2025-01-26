#include "chess_board.h"

#include <iostream>
#include <ostream>

int main(int argc, char **argv) {
    std::cout << "Chaac" << std::endl;

    chess_board board;
    board.print();
    board.move(UINT64_C(0x1) << (6 * 8 + 3), UINT64_C(0x1) << (4 * 8 + 3), player_type::WHITE);
    board.print();

    return 0;
}
