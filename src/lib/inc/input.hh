#pragma once

#include "board.hh"
#include "move.hh"

namespace ch::input {

ch::move read_move(const board &board);

} // namespace ch::input
