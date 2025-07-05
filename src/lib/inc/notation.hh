#pragma once

#include "types.hh"

#include <cassert>
#include <cstdint>

namespace ch::notation {

[[nodiscard]] constexpr bool is_one_piece(uint64_t board) {
    // Check if only one bit is set in the input
    return (board & (board - 1)) == 0;
}

[[nodiscard]] constexpr uint64_t from_square(types::square square) {
    const auto [file, rank] = square;
    assert(file >= 'a' && file <= 'h' && "File must be between 'a' and 'h'");
    assert(rank >= 1 && rank <= 8 && "Rank must be between 1 and 8");

    const uint8_t file_index = file - 'a';
    const uint8_t rank_index = rank - 1;
    const uint8_t bit_position = rank_index * 8 + file_index;

    return 1UL << bit_position;
}

[[nodiscard]] constexpr types::square to_square(uint64_t board) {
    assert(is_one_piece(board));

    // Find the position of the single set bit
    uint8_t bit_position = 0;
    uint64_t temp = board;
    while ((temp & 1UL) == 0) {
        temp >>= 1U;
        ++bit_position;
    }

    const char file = static_cast<char>((bit_position % 8) + 'a');
    const uint8_t rank = (bit_position / 8) + 1;

    return {file, rank};
}

} // namespace ch::notation
