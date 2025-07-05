#pragma once

#include "move.hh"
#include "notation.hh"
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
        this->pieces[0] |= 0xFFUL << 8U;

        // Blacks pawns
        this->pieces[6] |= 0xFFUL << (6U * 8U);
    }

    constexpr void init_rooks() {
        // Whites rooks
        this->pieces[1] |= notation::from_square({'a', 1});
        this->pieces[1] |= notation::from_square({'h', 1});

        // Blacks rooks
        this->pieces[7] |= notation::from_square({'a', 8});
        this->pieces[7] |= notation::from_square({'h', 8});
    }

    constexpr void init_knights() {
        // Whites knights
        this->pieces[2] |= notation::from_square({'b', 1});
        this->pieces[2] |= notation::from_square({'g', 1});

        // Blacks knights
        this->pieces[8] |= notation::from_square({'b', 8});
        this->pieces[8] |= notation::from_square({'g', 8});
    }

    constexpr void init_bishops() {
        // Whites bishops
        this->pieces[3] |= notation::from_square({'c', 1});
        this->pieces[3] |= notation::from_square({'f', 1});

        // Blacks bishops
        this->pieces[9] |= notation::from_square({'c', 8});
        this->pieces[9] |= notation::from_square({'f', 8});
    }

    constexpr void init_kings() {
        // Whites king
        this->pieces[4] |= notation::from_square({'e', 1});

        // Blacks king
        this->pieces[10] |= notation::from_square({'e', 8});
    }

    constexpr void init_queens() {
        // Whites queen
        this->pieces[5] |= notation::from_square({'d', 1});

        // Blacks queen
        this->pieces[11] |= notation::from_square({'d', 8});
    }

    [[nodiscard]] bool move_is_legal(const move &move) const;
    [[nodiscard]] bool move_is_legal_for_pawn(const move &move, int8_t direction) const;
    [[nodiscard]] bool move_is_legal_for_white_pawn(const move &move) const;
    [[nodiscard]] bool move_is_legal_for_black_pawn(const move &move) const;
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
    // pieces[0..6] are whites pieces represented as a bitboard, pieces[7..12] are blacks pieces. Each 64 bit integer
    // represents an 8x8 board where each bit represents a presence flag for whether or not the square is occupied by a
    // piece of that type. For example: pieces[0] are whites pawns where each bit tells us whether white has a pawn on
    // that square. Each int is LSB-first meaning a1 is bit 0 and h8 is bit 63.
    std::array<uint64_t, NUM_PIECES> pieces;
};

} // namespace ch

template <> struct std::formatter<ch::board> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const ch::board &p, std::format_context &ctx) const {
        std::stringstream out;
        // Need to traverse backwards so the last rank ends up at the top after formatting
        for (uint8_t rank = ch::board::NUM_ROWS; rank > 0; --rank) {
            for (uint8_t file = ch::board::NUM_COLS; file > 0; --file) {
                auto piece = p.find_piece(1UL << ((rank - 1) * 8U + (file - 1)));
                if (std::holds_alternative<ch::types::piece_t>(piece)) {
                    out << std::format("{}", std::get<ch::types::piece_t>(piece));
                } else {
                    out << ' ';
                }

                // Don't print trailing whitespace
                if (file != 1) {
                    out << ' ';
                }
            }
            out << '\n';
        }

        return std::format_to(ctx.out(), "{}", out.str());
    }
};
