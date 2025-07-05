#include "input.hh"
#include "board.hh"
#include "errors.hh"
#include "move.hh"
#include "notation.hh"
#include "types.hh"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <print>
#include <string>
#include <variant>

namespace ch::input {

namespace {

types::player_t current_player = types::player_t::WHITE;

void toggle_player() {
    current_player = current_player == types::player_t::WHITE ? types::player_t::BLACK : types::player_t::WHITE;
}

uint64_t read_square() {
    std::string in;
    std::cin >> in;

    // TODO(gremble0): better input validation
    assert(in.size() == 2);

    return notation::from_square({in.at(0), in.at(1) - '0'});
}

types::piece_position read_piece_source(const board &board) {
    std::println("[Player {}]: Select a piece", current_player);

    const uint64_t source = read_square();
    const auto at_square = board.find_piece(source);
    if (std::holds_alternative<types::empty_t>(at_square)) {
        ch::errors::warning("No piece at selected square");
        return read_piece_source(board);
    } else {
        assert(std::holds_alternative<types::piece_t>(at_square));
        return {std::get<types::piece_t>(at_square), source};
    }
}
uint64_t read_piece_destination() {
    (void)0;
    return 0;
}

} // namespace

ch::move read_move(const board &board) {
    const auto [piece_type, source] = read_piece_source(board);
    uint64_t dest = read_piece_destination();

    toggle_player();

    return {
        .source = source,
        .dest = dest,
        .piece = piece_type,
        .player = current_player,
    };
}

} // namespace ch::input
