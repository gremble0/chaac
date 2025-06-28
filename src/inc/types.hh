#pragma once

#include <cstdint>
#include <format>

enum class player_type : uint8_t {
    WHITE,
    BLACK,
};

enum class piece_type : uint8_t {
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

template <> struct std::formatter<piece_type> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const piece_type &p, std::format_context &ctx) const {
        switch (p) {
        case piece_type::WHITE_PAWN:
            return std::format_to(ctx.out(), "p");
        case piece_type::WHITE_ROOK:
            return std::format_to(ctx.out(), "r");
        case piece_type::WHITE_KNIGHT:
            return std::format_to(ctx.out(), "n");
        case piece_type::WHITE_BISHOP:
            return std::format_to(ctx.out(), "b");
        case piece_type::WHITE_KING:
            return std::format_to(ctx.out(), "k");
        case piece_type::WHITE_QUEEN:
            return std::format_to(ctx.out(), "q");

        case piece_type::BLACK_PAWN:
            return std::format_to(ctx.out(), "P");
        case piece_type::BLACK_ROOK:
            return std::format_to(ctx.out(), "R");
        case piece_type::BLACK_KNIGHT:
            return std::format_to(ctx.out(), "N");
        case piece_type::BLACK_BISHOP:
            return std::format_to(ctx.out(), "B");
        case piece_type::BLACK_KING:
            return std::format_to(ctx.out(), "K");
        case piece_type::BLACK_QUEEN:
            return std::format_to(ctx.out(), "Q");
        }

        return std::format_to(ctx.out(), "<unknown piece type>");
    }
};
