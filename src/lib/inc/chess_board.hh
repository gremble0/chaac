#pragma once

#include "chess_move.hh"
#include "types.hh"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <format>
#include <sstream>
#include <variant>

namespace ch {

class chess_board {
  public:
    friend class std::formatter<chess_board>;
    chess_board();

    void apply(const chess_move &move);

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

    [[nodiscard]] std::variant<types::piece_t, types::empty_t> find_piece(uint64_t square) const;

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

template <> struct std::formatter<ch::chess_board> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const ch::chess_board &p, std::format_context &ctx) const {
        std::stringstream out;
        for (size_t i = 0; i < ch::chess_board::NUM_ROWS; ++i) {
            for (size_t j = 0; j < ch::chess_board::NUM_COLS; ++j) {
                auto piece = p.find_piece(1UL << (i * 8 + j));
                if (std::holds_alternative<ch::types::piece_t>(piece)) {
                    out << std::format("{}", std::get<ch::types::piece_t>(piece));
                } else {
                    out << ' ';
                }

                if (j != ch::chess_board::NUM_COLS - 1) {
                    out << ' ';
                }
            }

            if (i != ch::chess_board::NUM_ROWS - 1) {
                out << '\n';
            }
        }

        return std::format_to(ctx.out(), "{}", out.str());
    }
};
