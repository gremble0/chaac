#pragma once

#include <cassert>
#include <cstdint>
#include <format>

namespace ch::types {

// a..h, 1..8 coordinate representing a human readable coordinate into an 8x8 chess board
using square = std::pair<char, uint8_t>;

enum class player_t : uint8_t {
    WHITE,
    BLACK,
};

enum class piece_t : uint8_t {
    WHITE_PAWN,
    WHITE_ROOK,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_KING,
    WHITE_QUEEN,
    BLACK_PAWN,
    BLACK_ROOK,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_KING,
    BLACK_QUEEN,
};

enum class empty_t : uint8_t { EMPTY };

enum class diagonal_movement_t : uint8_t { UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };

} // namespace ch::types

template <> struct std::formatter<ch::types::piece_t> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const ch::types::piece_t &p, std::format_context &ctx) const {
        switch (p) {
        case ch::types::piece_t::WHITE_PAWN:
            return std::format_to(ctx.out(), "P");
        case ch::types::piece_t::WHITE_ROOK:
            return std::format_to(ctx.out(), "R");
        case ch::types::piece_t::WHITE_KNIGHT:
            return std::format_to(ctx.out(), "N");
        case ch::types::piece_t::WHITE_BISHOP:
            return std::format_to(ctx.out(), "B");
        case ch::types::piece_t::WHITE_KING:
            return std::format_to(ctx.out(), "K");
        case ch::types::piece_t::WHITE_QUEEN:
            return std::format_to(ctx.out(), "Q");

        case ch::types::piece_t::BLACK_PAWN:
            return std::format_to(ctx.out(), "p");
        case ch::types::piece_t::BLACK_ROOK:
            return std::format_to(ctx.out(), "r");
        case ch::types::piece_t::BLACK_KNIGHT:
            return std::format_to(ctx.out(), "n");
        case ch::types::piece_t::BLACK_BISHOP:
            return std::format_to(ctx.out(), "b");
        case ch::types::piece_t::BLACK_KING:
            return std::format_to(ctx.out(), "k");
        case ch::types::piece_t::BLACK_QUEEN:
            return std::format_to(ctx.out(), "q");
        }

        assert(false && "Unknown piece type");
    }
};
