#include "chess_board.h"

#include <array>
#include <cstdint>
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
    // Whites pawns
    this->pieces[0] |= 0xff << 8; // a2..b2

    // Blacks pawns
    this->pieces[6] |= UINT64_C(0xff) << (6 * 8); // a7..h7
}

void chess_board::init_rooks() {
    // Whites rooks
    this->pieces[1] |= 1 << 7; // a1
    this->pieces[1] |= 1;      // h1

    // Blacks rooks
    this->pieces[7] |= UINT64_C(1) << (7 * 8);     // h8
    this->pieces[7] |= UINT64_C(1) << (7 * 8 + 7); // a8
}

void chess_board::init_knights() {
    // Whites knights
    this->pieces[2] |= 1 << 6; // b1
    this->pieces[2] |= 1 << 1; // g1

    // Blacks knights
    this->pieces[8] |= UINT64_C(1) << (7 * 8 + 6); // b8
    this->pieces[8] |= UINT64_C(1) << (7 * 8 + 1); // g8
}

void chess_board::init_bishops() {
    // Whites bishops
    this->pieces[3] |= 1 << 5; // c1
    this->pieces[3] |= 1 << 2; // f1

    // Blacks bishops
    this->pieces[9] |= UINT64_C(1) << (7 * 8 + 5); // c8
    this->pieces[9] |= UINT64_C(1) << (7 * 8 + 2); // f8
}

void chess_board::init_kings() {
    // Whites bishops
    this->pieces[4] |= 1 << 3; // e1

    // Blacks bishops
    this->pieces[10] |= UINT64_C(1) << (7 * 8 + 3); // e8
}

void chess_board::init_queens() {
    // Whites bishops
    this->pieces[5] |= 1 << 4; // d1

    // Blacks bishops
    this->pieces[11] |= UINT64_C(1) << (7 * 8 + 4); // e8
}
