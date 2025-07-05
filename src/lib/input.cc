#include "input.hh"
#include "move.hh"
#include "types.hh"
#include <cstdint>
#include <iostream>

namespace ch::input {

namespace {

types::piece_position read_piece_selection() {
    (void)0;
    return {};
}
uint64_t read_piece_destination() {
    (void)0;
    return 0;
}

} // namespace

ch::move read() {
    static types::player_t current_player = types::player_t::WHITE;
    current_player = current_player == types::player_t::WHITE ? types::player_t::BLACK : types::player_t::WHITE;

    const auto [piece_type, source] = read_piece_selection();
    uint64_t dest = read_piece_destination();

    return {
        .source = source,
        .dest = dest,
        .piece = piece_type,
        .player = current_player,
    };
}

} // namespace ch::input
