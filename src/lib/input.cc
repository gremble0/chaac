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

    // TODO(gremble0) this is a lil ugly and looks unsafe (assertion above kinda helps though)
    return notation::from_square({in.at(0), in.at(1) - '0'});
}

types::piece_position read_piece_source(const board &board) {
    std::println("[Player {}]: Select a square", current_player);

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
    // TODO(gremble0): player should probably be able to see what piece they have selected in this state
    std::println("[Player {}]: Where should the piece move?", current_player);

    // TODO(gremble0): error handling here transfers to the board class. Should find better architecture to keep all
    // error handling in one place. Currently we do error handling for selecting what piece to move in input handler and
    // then error handling of choosing where the piece should move in the board class. Board class' current error
    // handling also always results in crashing if it finds an error. This is not good UX
    return read_square();
}

} // namespace

ch::move read_move(const board &board) {
    const auto [piece_type, source] = read_piece_source(board);
    uint64_t dest = read_piece_destination();

    ch::move move = {
        .source = source,
        .dest = dest,
        .piece = piece_type,
        .player = current_player,
    };
    toggle_player();
    return move;
}

} // namespace ch::input
