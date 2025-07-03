#include "chess_board.hh"
#include "errors.hh"
#include "types.hh"

#include <array>
#include <cassert>
#include <cstdint>
#include <format>
#include <optional>
#include <ranges>

namespace ch {

chess_board::chess_board() : pieces() {
    this->init_pawns();
    this->init_rooks();
    this->init_knights();
    this->init_bishops();
    this->init_kings();
    this->init_queens();
}

void chess_board::apply(const chess_move &move) {
    auto piece = this->find_piece(move.source);
    if (!piece.has_value()) {
        errors::fatal("No piece at given square");
    }

    if (!this->piece_is_ours(piece.value(), move.player)) {
        errors::fatal("Cannot move opponents piece");
    }

    if (!this->move_is_legal(move)) {
        errors::fatal("Illegal move. Cannot move {}", piece.value());
    }

    auto piece_index = static_cast<uint8_t>(piece.value());
    assert(piece_index < NUM_PIECES);
    auto &piece_bits = this->pieces.at(piece_index);
    piece_bits ^= move.source; // Remove from source
    piece_bits |= move.dest;   // Add to destination
}

bool chess_board::piece_is_ours(types::piece_t piece_type, types::player_t player_type) const {
    auto piece_type_i = static_cast<uint8_t>(piece_type);
    assert(piece_type_i < NUM_PIECES);

    switch (player_type) {
    case types::player_t::WHITE:
        return piece_type_i < 6;

    case types::player_t::BLACK:
        return piece_type_i >= 6;
    }

    return false;
}

bool chess_board::move_is_legal(const chess_move &move) const {
    switch (move.piece) {
    case types::piece_t::WHITE_PAWN:
    case types::piece_t::BLACK_PAWN:
        return this->move_is_legal_for_pawn(move);

    case types::piece_t::WHITE_ROOK:
    case types::piece_t::BLACK_ROOK:
        return this->move_is_legal_for_rook(move);

    case types::piece_t::WHITE_KNIGHT:
    case types::piece_t::BLACK_KNIGHT:
        return this->move_is_legal_for_knight(move);

    case types::piece_t::WHITE_BISHOP:
    case types::piece_t::BLACK_BISHOP:
        return this->move_is_legal_for_bishop(move);

    case types::piece_t::WHITE_KING:
    case types::piece_t::BLACK_KING:
        return this->move_is_legal_for_king(move);

    case types::piece_t::WHITE_QUEEN:
    case types::piece_t::BLACK_QUEEN:
        return this->move_is_legal_for_queen(move);
    }

    errors::fatal("Tried to move unknown chess piece {}", move);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

bool chess_board::move_is_legal_for_pawn(const chess_move &move) const {
    auto dest_is_occupied = this->find_piece(move.dest).has_value();

    // Determine direction: white pawns move up (+1), black pawns move down (-1)
    int8_t direction = (move.player == types::player_t::WHITE) ? 1 : -1;

    if (move.player == types::player_t::BLACK) {
        assert(move.piece == types::piece_t::BLACK_PAWN);
    } else if (move.player == types::player_t::WHITE) {
        assert(move.piece == types::piece_t::WHITE_PAWN);
    } else {
        assert(false);
    }

    // Forward moves (1 or 2 squares)
    if ((move.dest == chess_move::move(move.source, 0, direction) ||
         move.dest == chess_move::move(move.source, 0, static_cast<int8_t>(direction * 2))) &&
        !dest_is_occupied) {
        return true;
    }

    // Diagonal captures
    if ((move.dest == chess_move::move(move.source, -1, direction) ||
         move.dest == chess_move::move(move.source, 1, direction)) &&
        dest_is_occupied) {
        return true;
    }

    // There is also en passant but this is way too complicated. Maybe in the future...

    return false;
}

bool chess_board::move_is_legal_for_rook(const chess_move &move) const {
    // Rooks can move/capture as many squares as it wants vertically if there are no pieces in its
    // path

    // Rooks can move/capture as many squares as it wants horizontally if there are no pieces in its
    // path

    return true;
}

bool chess_board::move_is_legal_for_knight(const chess_move &move) const {
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

bool chess_board::move_is_legal_for_bishop(const chess_move &move) const {
    // Bishops can move/capture as many squares as it wants diagonally from bottom+left to top+right
    // if there are no pieces in its path (/)

    // Bishops can move/capture as many squares as it wants diagonally from top+left to bottom+right
    // if there are no pieces in its path (\)

    return true;
}

bool chess_board::move_is_legal_for_king(const chess_move &move) const {
    // Kings can move/capture 1 square vertically

    // Kings can move/capture 1 square horizontally

    // Kings can move/capture 1 square diagonally from bottom+left to top+right (/)

    // Kings can move/capture 1 square diagonally from top+left to bototm+right (\)

    return true;
}

bool chess_board::move_is_legal_for_queen(const chess_move &move) const {
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

std::optional<types::piece_t> chess_board::find_piece(uint64_t square) const {
    for (const auto &[i, piece] : std::views::enumerate(this->pieces)) {
        if (piece & square) {
            return types::piece_t(i);
        }
    }

    return std::nullopt;
}

void chess_board::init_pawns() {
    // Whites pawns
    this->pieces[0] |= 0xffUL << (6U * 8);

    // Blacks pawns
    this->pieces[6] |= 0xffUL << 8U;
}

void chess_board::init_rooks() {
    // Whites rooks
    this->pieces[1] |= 1UL << (7U * 8);
    this->pieces[1] |= 1UL << (7U * 8 + 7);

    // Blacks rooks
    this->pieces[7] |= 1UL << 7U;
    this->pieces[7] |= 1UL;
}

void chess_board::init_knights() {
    // Whites knights
    this->pieces[2] |= 1UL << (7U * 8 + 6);
    this->pieces[2] |= 1UL << (7U * 8 + 1);

    // Blacks knights
    this->pieces[8] |= 1UL << 6U;
    this->pieces[8] |= 1UL << 1U;
}

void chess_board::init_bishops() {
    // Whites bishops
    this->pieces[3] |= 1UL << (7U * 8 + 5);
    this->pieces[3] |= 1UL << (7U * 8 + 2);

    // Blacks bishops
    this->pieces[9] |= 1UL << 5U;
    this->pieces[9] |= 1UL << 2U;
}

void chess_board::init_kings() {
    // Whites king
    this->pieces[4] |= 1UL << (7U * 8 + 3);

    // Blacks king
    this->pieces[10] |= 1UL << 3U;
}

void chess_board::init_queens() {
    // Whites queen
    this->pieces[5] |= 1UL << (7U * 8 + 4);

    // Blacks queen
    this->pieces[11] |= 1UL << 4U;
}

} // namespace ch
