#pragma once

#include "types.hh"

#include <cassert>
#include <cstdint>
#include <format>

namespace ch {

struct chess_move {
    uint64_t source;
    uint64_t dest;
    types::piece_t piece;
    types::player_t player;

    [[nodiscard]] static constexpr bool is_one_piece(uint64_t layer) {
        // Check if only one bit is set in the input
        return (layer & (layer - 1)) == 0;
    }

    /**
     * Move source by x steps along x axis and y steps along y axis.
     * @param x positive number means move x steps to the right, negative means move x steps to the left
     * @param y positive number means move y steps upward, negative means move y steps downward
     */
    [[nodiscard]] static constexpr uint64_t move(uint64_t source, int8_t x, int8_t y) {
        // TODO(gremble): bounds checking?
        assert(x != 0 && y != 0);
        assert(chess_move::is_one_piece(source));

        // Handle any x axis movement (left to right)
        if (x < 0) {
            source = source >> static_cast<uint8_t>(-x);
        } else if (x > 0) {
            source = source << static_cast<uint8_t>(x);
        }

        // Handle any y axis movement (bottom to top)
        if (y < 0) {
            source = source >> static_cast<uint8_t>(-y * 8);
        } else if (y > 0) {
            source = source << static_cast<uint8_t>(y * 8);
        }

        return source;
    }
};

} // namespace ch

template <> struct std::formatter<ch::chess_move> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format([[maybe_unused]] const ch::chess_move &p, std::format_context &ctx) const {
        // TODO(gremble): implement this
        return std::format_to(ctx.out(), "<move>");
    }
};
