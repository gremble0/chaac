#pragma once

#include <cassert>
#include <cstdint>

namespace ch::notation {

static constexpr uint64_t from_notation(char file, uint8_t rank) {
    assert(file >= 'a' && file <= 'h' && "File must be between 'a' and 'h'");
    assert(rank >= 1 && rank <= 8 && "Rank must be between 1 and 8");

    const uint8_t file_index = file - 'a';
    const uint8_t rank_index = rank - 1;
    const uint8_t bit_position = 63 - (rank_index * 8 + file_index);

    return 1UL << bit_position;
}

} // namespace ch::notation
