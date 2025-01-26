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
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            for (int k = 0; k < 12; ++k) {
                if (pieces[k] & UINT64_C(1) << (i * 8 + j)) {
                    std::cout << pieces_strings[k] << ' ';
                    break;
                }
            }
            std::cout << ' ';
        }
        std::cout << '\n';
    }
}

void chess_board::init_pawns() {
    // Whites pawns
    this->pieces[0] |= UINT64_C(0xff) << (6 * 8);

    // Blacks pawns
    this->pieces[6] |= 0xff << 8;
}

void chess_board::init_rooks() {
    // Whites rooks
    this->pieces[1] |= UINT64_C(1) << (7 * 8);
    this->pieces[1] |= UINT64_C(1) << (7 * 8 + 7);

    // Blacks rooks
    this->pieces[7] |= 1 << 7;
    this->pieces[7] |= 1;
}

void chess_board::init_knights() {
    // Whites knights
    this->pieces[2] |= UINT64_C(1) << (7 * 8 + 6);
    this->pieces[2] |= UINT64_C(1) << (7 * 8 + 1);

    // Blacks knights
    this->pieces[8] |= 1 << 6;
    this->pieces[8] |= 1 << 1;
}

void chess_board::init_bishops() {
    // Whites bishops
    this->pieces[3] |= UINT64_C(1) << (7 * 8 + 5);
    this->pieces[3] |= UINT64_C(1) << (7 * 8 + 2);

    // Blacks bishops
    this->pieces[9] |= 1 << 5;
    this->pieces[9] |= 1 << 2;
}

void chess_board::init_kings() {
    // Whites king
    this->pieces[4] |= UINT64_C(1) << (7 * 8 + 3);

    // Blacks king
    this->pieces[10] |= 1 << 3;
}

void chess_board::init_queens() {
    // Whites queen
    this->pieces[5] |= UINT64_C(1) << (7 * 8 + 4);

    // Blacks queen
    this->pieces[11] |= 1 << 4;
}
