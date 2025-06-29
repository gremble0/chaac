#pragma once

#include "types.hh"

#include <cstdint>
#include <format>

namespace ch {

struct chess_move {
    uint64_t source;
    uint64_t dest;
    types::piece_t piece;
    types::player_t player;
};

} // namespace ch

template <> struct std::formatter<ch::chess_move> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format([[maybe_unused]] const ch::chess_move &p, std::format_context &ctx) const {
        // TODO(gremble): implement this
        return std::format_to(ctx.out(), "<move>");
    }
};
