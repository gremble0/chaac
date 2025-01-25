#include "chess_board.h"

#include <array>
#include <iostream>
#include <ostream>

chess_board::chess_board() : pieces() {
    this->init_pawns();
    this->init_rooks();
    this->init_knights();
    this->init_bishops();
    this->init_kings();
    this->init_queens();
}

void chess_board::print() {
    for (const auto piece : this->pieces)
        std::cout << piece << std::endl;
}

void chess_board::init_pawns() {
    // Whites pawns (second row from bottom)
    this->pieces[0] |= UINT64_C(0xff) << 8;

    // Blacks pawns (second row from top)
    this->pieces[6] |= UINT64_C(0xff) << (7 * 8);
}

void chess_board::init_rooks() {}

void chess_board::init_knights() {}

void chess_board::init_bishops() {}

void chess_board::init_kings() {}

void chess_board::init_queens() {}

