#include "board.hh"
#include "errors.hh"
#include "types.hh"

#include <array>
#include <cassert>
#include <cstdint>
#include <format>
#include <ranges>
#include <variant>

namespace ch {

board::board() : pieces() {
    this->init_pawns();
    this->init_rooks();
    this->init_knights();
    this->init_bishops();
    this->init_kings();
    this->init_queens();
}

void board::apply(const move &move) {
    auto piece = this->find_piece(move.source);
    if (std::holds_alternative<types::empty_t>(piece)) {
        errors::fatal("No piece at given square");
    }
    assert(std::holds_alternative<types::piece_t>(piece));
    auto piece_value = std::get<types::piece_t>(piece);

    if (!this->piece_is_ours(piece_value, move.player)) {
        errors::fatal("Cannot move opponents piece");
    }

    if (!this->move_is_legal(move)) {
        errors::fatal("Illegal move. Cannot move {}", piece_value);
    }

    auto piece_index = static_cast<uint8_t>(piece_value);
    assert(piece_index < NUM_PIECES);
    auto &piece_bits = this->pieces.at(piece_index);
    piece_bits ^= move.source; // Remove from source
    piece_bits |= move.dest;   // Add to destination
}

bool board::piece_is_ours(types::piece_t piece_type, types::player_t player_type) const {
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

bool board::move_is_legal(const move &move) const {
    switch (move.piece) {
    case types::piece_t::WHITE_PAWN:
        return this->move_is_legal_for_white_pawn(move);
    case types::piece_t::BLACK_PAWN:
        return this->move_is_legal_for_black_pawn(move);

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

bool board::move_is_legal_for_pawn(const move &move, int8_t direction) const {
    auto dest_is_occupied = std::holds_alternative<types::piece_t>(this->find_piece(move.dest));

    // Forward moves (1 or 2 squares)
    if ((move.dest == move::get_dest(move.source, 0, direction) ||
         move.dest == move::get_dest(move.source, 0, static_cast<int8_t>(2 * direction))) &&
        !dest_is_occupied) {
        return true;
    }

    // Diagonal captures
    if ((move.dest == move::get_dest(move.source, -1, direction) ||
         move.dest == move::get_dest(move.source, 1, direction)) &&
        dest_is_occupied) {
        return true;
    }

    // There is also en passant but this is way too complicated. Maybe in the future...
    return false;
}

bool board::move_is_legal_for_white_pawn(const move &move) const {
    assert(move.piece == types::piece_t::WHITE_PAWN);
    return this->move_is_legal_for_pawn(move, 1);
}

bool board::move_is_legal_for_black_pawn(const move &move) const {
    assert(move.piece == types::piece_t::BLACK_PAWN);
    return this->move_is_legal_for_pawn(move, -1);
}

bool board::move_is_legal_for_rook(const move &move) const {
    // Rooks can move/capture as many squares as it wants vertically if there are no pieces in its
    // path

    // Rooks can move/capture as many squares as it wants horizontally if there are no pieces in its
    // path

    return true;
}

bool board::move_is_legal_for_knight(const move &move) const {
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

bool board::move_is_legal_for_bishop(const move &move) const {
    // Bishops can move/capture as many squares as it wants diagonally from bottom+left to top+right
    // if there are no pieces in its path (/)

    // Bishops can move/capture as many squares as it wants diagonally from top+left to bottom+right
    // if there are no pieces in its path (\)

    return true;
}

bool board::move_is_legal_for_king(const move &move) const {
    // Kings can move/capture 1 square vertically

    // Kings can move/capture 1 square horizontally

    // Kings can move/capture 1 square diagonally from bottom+left to top+right (/)

    // Kings can move/capture 1 square diagonally from top+left to bototm+right (\)

    return true;
}

bool board::move_is_legal_for_queen(const move &move) const {
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

std::variant<types::piece_t, types::empty_t> board::find_piece(uint64_t board) const {
    for (const auto &[i, piece] : std::views::enumerate(this->pieces)) {
        if (piece & board) {
            return types::piece_t(i);
        }
    }

    return types::empty_t::EMPTY;
}

} // namespace ch
