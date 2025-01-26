#include "chess_board.h"

#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <ostream>

chess_board::chess_board() : pieces() {
    this->init_pawns();
    this->init_rooks();
    this->init_knights();
    this->init_bishops();
    this->init_kings();
    this->init_queens();
}

void chess_board::move(uint64_t source, uint64_t dest, player_type player_type) {
    auto piece = this->find_piece(source);
    if (!piece.has_value())
        this->fatal("No piece at given square");

    if (!this->piece_is_ours(piece.value(), player_type))
        this->fatal("Cannot move opponents piece");

    if (this->move_is_legal(source, dest, piece.value())) {
        this->pieces[piece.value()] ^= source; // Remove from source
        this->pieces[piece.value()] |= dest;   // Add to destination
    } else {
        this->fatal("Illegal move");
    }
}

bool chess_board::piece_is_ours(uint8_t piece, player_type player_type) {
    switch (player_type) {
    case player_type::WHITE:
        return piece < 6;

    case player_type::BLACK:
        return piece >= 6;
    }

    return false;
}

bool chess_board::move_is_legal(uint64_t source, uint64_t dest, uint8_t piece) { return true; }

std::optional<uint8_t> chess_board::find_piece(uint64_t square) {
    for (int i = 0; i < 12; ++i)
        if (pieces[i] & square)
            return i;

    return std::nullopt;
}

void chess_board::fatal(const char *msg) {
    std::cerr << msg << std::endl;
    exit(1);
}

void chess_board::print() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            auto piece = find_piece(UINT64_C(1) << (i * 8 + j));
            if (piece.has_value())
                std::cout << pieces_strings[piece.value()] << ' ';
            else
                std::cout << "  ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
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
