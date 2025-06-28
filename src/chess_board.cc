#include "chess_board.h"
#include "errors.h"

#include <array>
#include <cstdint>
#include <cstdlib>
#include <optional>
#include <print>

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
        errors::fatal("No piece at given square");

    if (!this->piece_is_ours(piece.value(), player_type))
        errors::fatal("Cannot move opponents piece at {}", dest);

    if (this->move_is_legal(source, dest, piece.value())) {
        this->pieces[static_cast<uint8_t>(piece.value())] ^= source; // Remove from source
        this->pieces[static_cast<uint8_t>(piece.value())] |= dest;   // Add to destination
    } else {
        errors::fatal("Illegal move");
    }
}

bool chess_board::piece_is_ours(piece_type piece_type, player_type player_type) const {
    switch (player_type) {
    case player_type::WHITE:
        return static_cast<uint8_t>(piece_type) < 6;

    case player_type::BLACK:
        return static_cast<uint8_t>(piece_type) >= 6;
    }

    return false;
}

bool chess_board::move_is_legal(uint64_t source, uint64_t dest, piece_type piece_type) const {
    switch (piece_type) {
    case piece_type::WHITE_PAWN:
    case piece_type::BLACK_PAWN:
        return this->move_is_legal_for_pawn(source, dest);

    case piece_type::WHITE_ROOK:
    case piece_type::BLACK_ROOK:
        return this->move_is_legal_for_rook(source, dest);

    case piece_type::WHITE_KNIGHT:
    case piece_type::BLACK_KNIGHT:
        return this->move_is_legal_for_knight(source, dest);

    case piece_type::WHITE_BISHOP:
    case piece_type::BLACK_BISHOP:
        return this->move_is_legal_for_bishop(source, dest);

    case piece_type::WHITE_KING:
    case piece_type::BLACK_KING:
        return this->move_is_legal_for_king(source, dest);

    case piece_type::WHITE_QUEEN:
    case piece_type::BLACK_QUEEN:
        return this->move_is_legal_for_queen(source, dest);
    }

    errors::fatal("Tried to move unknown chess piece {}", static_cast<uint8_t>(piece_type));
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

bool chess_board::move_is_legal_for_pawn(uint64_t source, uint64_t dest) const {
    // Pawns can move 1 square forward if there is no piece there

    // Pawns can move 2 squares forward if there is no pieces in its path

    // Pawns can capture 1 square diagonally if the opponent has a piece there

    // There is also en passant, but that is way too complicated. Could maybe implement in the
    // future

    return true;
}

bool chess_board::move_is_legal_for_rook(uint64_t source, uint64_t dest) const {
    // Rooks can move/capture as many squares as it wants vertically if there are no pieces in its
    // path

    // Rooks can move/capture as many squares as it wants horizontally if there are no pieces in its
    // path

    return true;
}

bool chess_board::move_is_legal_for_knight(uint64_t source, uint64_t dest) const {
    // Knights can move/capture 2 squares forward and then 1 to the right

    // Knights can move/capture 2 squares forward and then 1 to the left

    // Knights can move/capture 2 squares to the right and then 1 forward

    // Knights can move/capture 2 squares to the right and then 1 back

    // Knights can move/capture 2 squares back and then 1 to the right

    // Knights can move/capture 2 squares back and then 1 to the left

    // Knights can move/capture 2 squares to the left and then 1 forward

    // Knights can move/capture 2 squares to the left and then 1 back

    return true;
}

bool chess_board::move_is_legal_for_bishop(uint64_t source, uint64_t dest) const {
    // Bishops can move/capture as many squares as it wants diagonally from bottom+left to top+right
    // if there are no pieces in its path (/)

    // Bishops can move/capture as many squares as it wants diagonally from top+left to bottom+right
    // if there are no pieces in its path (\)

    return true;
}

bool chess_board::move_is_legal_for_king(uint64_t source, uint64_t dest) const {
    // Kings can move/capture 1 square vertically

    // Kings can move/capture 1 square horizontally

    // Kings can move/capture 1 square diagonally from bottom+left to top+right (/)

    // Kings can move/capture 1 square diagonally from top+left to bototm+right (\)

    return true;
}

bool chess_board::move_is_legal_for_queen(uint64_t source, uint64_t dest) const {
    // Queens can move/capture as many squares as it wants vertically if there are no pieces in its
    // path

    // Queens can move/capture as many squares as it wants diagonally from bottom+left to top+right
    // if there are no pieces in its path (/)

    // Queens can move/capture as many squares as it wants horizontally if there are no pieces in
    // its path

    // Queens can move/capture as many squares as it wants diagonally from top+left to bottom+right
    // if there are no pieces in its path (\)

    return true;
}

#pragma GCC diagnostic pop

std::optional<piece_type> chess_board::find_piece(uint64_t square) const {
    for (size_t i = 0; i < chess_board::NUM_PIECES; ++i) {
        if (this->pieces[i] & square) {
            return piece_type(i);
        }
    }

    return std::nullopt;
}

void chess_board::print() {
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            auto piece = find_piece(1U << (i * 8 + j));
            if (piece.has_value())
                std::print("{}", chess_board::pieces_strings[static_cast<uint8_t>(piece.value())]);
            else
                std::print("  ");
        }
        std::println();
    }
    std::println();
}

void chess_board::init_pawns() {
    // Whites pawns
    this->pieces[0] |= 0xffUL << (6UL * 8);

    // Blacks pawns
    this->pieces[6] |= 0xffUL << 8UL;
}

void chess_board::init_rooks() {
    // Whites rooks
    this->pieces[1] |= 1UL << (7U * 8);
    this->pieces[1] |= 1UL << (7U * 8 + 7);

    // Blacks rooks
    this->pieces[7] |= 1U << 7U;
    this->pieces[7] |= 1U;
}

void chess_board::init_knights() {
    // Whites knights
    this->pieces[2] |= 1UL << (7U * 8 + 6);
    this->pieces[2] |= 1UL << (7U * 8 + 1);

    // Blacks knights
    this->pieces[8] |= 1U << 6U;
    this->pieces[8] |= 1U << 1U;
}

void chess_board::init_bishops() {
    // Whites bishops
    this->pieces[3] |= 1UL << (7U * 8 + 5);
    this->pieces[3] |= 1UL << (7U * 8 + 2);

    // Blacks bishops
    this->pieces[9] |= 1U << 5U;
    this->pieces[9] |= 1U << 2U;
}

void chess_board::init_kings() {
    // Whites king
    this->pieces[4] |= 1UL << (7U * 8 + 3);

    // Blacks king
    this->pieces[10] |= 1U << 3U;
}

void chess_board::init_queens() {
    // Whites queen
    this->pieces[5] |= 1UL << (7U * 8 + 4);

    // Blacks queen
    this->pieces[11] |= 1U << 4U;
}
