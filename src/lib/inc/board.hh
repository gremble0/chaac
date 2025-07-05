#pragma once

#include "move.hh"
#include "types.hh"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <format>
#include <sstream>
#include <variant>

namespace ch {

class board {
  public:
    friend class std::formatter<board>;
    board();

    void apply(const move &move);

  private:
    constexpr void init_pawns() {
        // Whites pawns
        this->pieces[0] |= 0xffUL << (6U * 8);

        // Blacks pawns
        this->pieces[6] |= 0xffUL << 8U;
    }

    constexpr void init_rooks() {
        // Whites rooks
        this->pieces[1] |= 1UL << (7U * 8);
        this->pieces[1] |= 1UL << (7U * 8 + 7);

        // Blacks rooks
        this->pieces[7] |= 1UL << 7U;
        this->pieces[7] |= 1UL;
    }

    constexpr void init_knights() {
        // Whites knights
        this->pieces[2] |= 1UL << (7U * 8 + 6);
        this->pieces[2] |= 1UL << (7U * 8 + 1);

        // Blacks knights
        this->pieces[8] |= 1UL << 6U;
        this->pieces[8] |= 1UL << 1U;
    }

    constexpr void init_bishops() {

        // Whites bishops
        this->pieces[3] |= 1UL << (7U * 8 + 5);
        this->pieces[3] |= 1UL << (7U * 8 + 2);

        // Blacks bishops
        this->pieces[9] |= 1UL << 5U;
        this->pieces[9] |= 1UL << 2U;
    }

    constexpr void init_kings() {
        // Whites king
        this->pieces[4] |= 1UL << (7U * 8 + 3);

        // Blacks king
        this->pieces[10] |= 1UL << 3U;
    }

    constexpr void init_queens() {
        // Whites queen
        this->pieces[5] |= 1UL << (7U * 8 + 4);

        // Blacks queen
        this->pieces[11] |= 1UL << 4U;
    }

    [[nodiscard]] bool move_is_legal(const move &move) const;
    [[nodiscard]] bool move_is_legal_for_pawn(const move &move) const;
    [[nodiscard]] bool move_is_legal_for_rook(const move &move) const;
    [[nodiscard]] bool move_is_legal_for_knight(const move &move) const;
    [[nodiscard]] bool move_is_legal_for_bishop(const move &move) const;
    [[nodiscard]] bool move_is_legal_for_king(const move &move) const;
    [[nodiscard]] bool move_is_legal_for_queen(const move &move) const;

    [[nodiscard]] bool piece_is_ours(types::piece_t piece_type, types::player_t player_type) const;

    [[nodiscard]] std::variant<types::piece_t, types::empty_t> find_piece(uint64_t square) const;

    static constexpr size_t NUM_PIECES = 12;
    static constexpr size_t NUM_ROWS = 8;
    static constexpr size_t NUM_COLS = 8;

    // TODO(gremble0): make this an array of variants of piece_t or empty?
    // pieces[0..6] are whites pieces represented as a bitboard. Each 64 bit integer represents an
    // 8x8 board where each bit represents a presence flag for whether or not the square is
    // occupied. For example: pieces[0] are whites pawns where each bit tells us whether white has a
    // pawn on that square.
    std::array<uint64_t, NUM_PIECES> pieces;
};

} // namespace ch

template <> struct std::formatter<ch::board> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const ch::board &p, std::format_context &ctx) const {
        std::stringstream out;
        for (size_t i = 0; i < ch::board::NUM_ROWS; ++i) {
            for (size_t j = 0; j < ch::board::NUM_COLS; ++j) {
                auto piece = p.find_piece(1UL << (i * 8 + j));
                if (std::holds_alternative<ch::types::piece_t>(piece)) {
                    out << std::format("{}", std::get<ch::types::piece_t>(piece));
                } else {
                    out << ' ';
                }

                // Don't print trailing whitespace
                if (j != ch::board::NUM_COLS - 1) {
                    out << ' ';
                }
            }
            out << '\n';
        }

        return std::format_to(ctx.out(), "{}", out.str());
    }
};
