#pragma once

#include "chess_move.hh"
#include "types.hh"

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
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

    [[nodiscard]] static constexpr bool is_one_piece(uint64_t layer) {
        return (layer & (layer - 1)) == 0;
    }

    [[nodiscard]] static constexpr uint64_t move_vertical(uint64_t source, int8_t n_ranks) {
        assert(n_ranks != 0);
        assert(chess_board::is_one_piece(source));

        if (n_ranks < 0) {
            return source << static_cast<uint8_t>(-n_ranks * 8);
        } else {
            return source >> static_cast<uint8_t>(n_ranks * 8);
        }
    }

    [[nodiscard]] static constexpr uint64_t move_diagonal(uint64_t source, uint8_t n_steps,
                                                          types::diagonal_movement_t direction) {
        assert(n_steps != 0);
        assert(chess_board::is_one_piece(source));

        switch (direction) {
        case types::diagonal_movement_t::UP_LEFT:
            return source << (n_steps * 8U - n_steps);
        case types::diagonal_movement_t::UP_RIGHT:
            return source << (n_steps * 8U + n_steps);
        case types::diagonal_movement_t::DOWN_LEFT:
            return source >> (n_steps * 8U - n_steps);
        case types::diagonal_movement_t::DOWN_RIGHT:
            return source >> (n_steps * 8U + n_steps);
        }

        assert(false);
    }

    [[nodiscard]] bool piece_is_ours(types::piece_t piece_type, types::player_t player_type) const;

    [[nodiscard]] std::optional<types::piece_t> find_piece(uint64_t square) const;

    static constexpr size_t NUM_PIECES = 12;
    static constexpr size_t NUM_ROWS = 8;
    static constexpr size_t NUM_COLS = 8;

    // pieces[0..6] are whites pieces represented as a bitboard. Each 64 bit integer represents an
    // 8x8 board where each bit represents a presence flag for whether or not the square is
    // occupied. For example: pieces[0] are whites pawns where each bit tells us whether white has a
    // pawn on that square.
    std::array<uint64_t, NUM_PIECES> pieces;
};

} // namespace ch
