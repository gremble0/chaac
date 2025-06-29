#pragma once

#include "chess_move.hh"
#include "types.hh"

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>

namespace ch {

class chess_board {
  public:
    chess_board();

    void apply(const chess_move &move);
    void print();

  private:
    void init_pawns();
    void init_rooks();
    void init_knights();
    void init_bishops();
    void init_kings();
    void init_queens();

    [[nodiscard]] bool move_is_legal(const chess_move &move) const;
    [[nodiscard]] bool move_is_legal_for_pawn(const chess_move &move) const;
    [[nodiscard]] bool move_is_legal_for_rook(const chess_move &move) const;
    [[nodiscard]] bool move_is_legal_for_knight(const chess_move &move) const;
    [[nodiscard]] bool move_is_legal_for_bishop(const chess_move &move) const;
    [[nodiscard]] bool move_is_legal_for_king(const chess_move &move) const;
    [[nodiscard]] bool move_is_legal_for_queen(const chess_move &move) const;

    [[nodiscard]] bool piece_is_ours(types::piece_t piece_type, types::player_t player_type) const;

    [[nodiscard]] std::optional<types::piece_t> find_piece(uint64_t square) const;

    static constexpr std::size_t NUM_PIECES = 12;
    static constexpr std::size_t NUM_ROWS = 8;
    static constexpr std::size_t NUM_COLS = 8;

    // pieces[0..6] are whites pieces represented as a bitboard. Each 64 bit integer represents an
    // 8x8 board where each bit represents a presence flag for whether or not the square is
    // occupied. For example: pieces[0] are whites pawns where each bit tells us whether white has a
    // pawn on that square.
    std::array<uint64_t, NUM_PIECES> pieces;

    static constexpr auto pieces_strings =
        std::to_array({"P", "R", "N", "B", "K", "Q", "p", "r", "n", "b", "k", "q"});
};

} // namespace ch
