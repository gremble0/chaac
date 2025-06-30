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
        return (layer & (layer - 1)) == 0;
    }

    [[nodiscard]] static constexpr uint64_t move_vertical(uint64_t source, int8_t n_ranks) {
        assert(n_ranks != 0);
        assert(chess_move::is_one_piece(source));

        if (n_ranks < 0) {
            return source << static_cast<uint8_t>(-n_ranks * 8);
        } else {
            return source >> static_cast<uint8_t>(n_ranks * 8);
        }
    }

    [[nodiscard]] static constexpr uint64_t move_diagonal(uint64_t source, uint8_t n_steps,
                                                          types::diagonal_movement_t direction) {
        assert(n_steps != 0);
        assert(chess_move::is_one_piece(source));

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
};

} // namespace ch

template <> struct std::formatter<ch::chess_move> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format([[maybe_unused]] const ch::chess_move &p, std::format_context &ctx) const {
        // TODO(gremble): implement this
        return std::format_to(ctx.out(), "<move>");
    }
};
