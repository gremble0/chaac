#include <board.hh>

#include <print>

int main(int /*argc*/, const char *const * /*argv*/) {
    std::println("Chaac - a chess engine");

    ch::board board;
    std::print("{}", board);
    // board.move(0x1UL << (7U * 8 + 3), 0x1UL << (4U * 8 + 3), player_type::WHITE);
    // board.print();

    return 0;
}
