#pragma once

#include <cstdint>

namespace ch::notation {

template <char file, uint8_t rank> static constexpr uint64_t from_notation() {
    static_assert(file >= 'a' && file <= 'h');
    static_assert(rank >= 1 && rank <= 8);

    // Convert file ('a' - 'h') to column (0 - 7)
    constexpr uint8_t file_index = file - 'a';

    // Convert rank (1 - 8) to row (7-0)
    // rank 1 is bottom row (row 7 in your representation)
    // rank 8 is top row (row 0 in your representation)
    constexpr uint8_t rank_index = 8 - rank;

    // Calculate bit position
    // Your layout: bit 63 is top-left, bit 0 is bottom-right
    constexpr uint8_t bit_position = rank_index * 8 + file_index;

    return 1ULL << bit_position;
}

} // namespace ch::notation
