#pragma once

#include "types.hh"

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>

class chess_board {
  public:
    chess_board();

    void move(uint64_t source, uint64_t dest, player_type player);

    void print();

  private:
    void init_pawns();
    void init_rooks();
    void init_knights();
    void init_bishops();
    void init_kings();
    void init_queens();

    [[nodiscard]] bool move_is_legal(uint64_t source, uint64_t dest, piece_type piece_type) const;
    [[nodiscard]] bool move_is_legal_for_pawn(uint64_t source, uint64_t dest) const;
    [[nodiscard]] bool move_is_legal_for_rook(uint64_t source, uint64_t dest) const;
    [[nodiscard]] bool move_is_legal_for_knight(uint64_t source, uint64_t dest) const;
    [[nodiscard]] bool move_is_legal_for_bishop(uint64_t source, uint64_t dest) const;
    [[nodiscard]] bool move_is_legal_for_king(uint64_t source, uint64_t dest) const;
    [[nodiscard]] bool move_is_legal_for_queen(uint64_t source, uint64_t dest) const;

    [[nodiscard]] bool piece_is_ours(piece_type piece_type, player_type player_type) const;

    [[nodiscard]] std::optional<piece_type> find_piece(uint64_t square) const;

    static constexpr std::size_t NUM_PIECES = 12;
    static constexpr std::size_t NUM_ROWS = 8;
    static constexpr std::size_t NUM_COLS = 8;

    // pieces[0..6] are whites pieces represented as a bitboard. Each 64 bit integer represents an
    // 8x8 board where each bit represents a presence flag for whether or not the square is
    // occupied. For example: pieces[0] are whites pawns where each bit tells us whether white has a
    // pawn on that square.
    std::array<uint64_t, NUM_PIECES> pieces;
};
