#pragma once

#include "types.hh"

#include <cstdint>

namespace ch {

struct chess_move {
    uint64_t source;
    uint64_t dest;
    types::piece_t piece;
    types::player_t player;
};

} // namespace ch
