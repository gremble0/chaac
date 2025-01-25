#include <array>
#include <cstdint>
#include <iostream>
#include <ostream>

class chess_board {
  public:
    chess_board();

  private:
    void init_pawns();
    void init_rooks();
    void init_knights();
    void init_bishops();
    void init_kings();
    void init_queens();

    // pieces[0..6] are whites pieces represented as a bitboard. Each 64 bit integer represents an
    // 8x8 board where each bit represents a presence flag for whether or not the square is
    // occupied. For example: pieces[0] are whites pawns where each bit tells us whether white has a
    // pawn on that square.
    std::array<uint64_t, 12> pieces;
};

chess_board::chess_board() : pieces() {
    this->init_pawns();
    this->init_rooks();
    this->init_knights();
    this->init_bishops();
    this->init_kings();
    this->init_queens();
}

void chess_board::init_pawns() {}

int main(int argc, char **argv) {
    std::cout << "Chaac" << std::endl;

    chess_board board;

    return 0;
}
