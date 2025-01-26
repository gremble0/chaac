#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string_view>

enum class player_type {
    WHITE,
    BLACK,
};

class chess_board {
  public:
    chess_board();

    void move(uint64_t source, uint64_t dest, player_type player);

    void print();

  private:
    void init_pawns();
    void init_rooks();
    void init_knights();
    void init_bishops();
    void init_kings();
    void init_queens();

    bool piece_is_ours(uint8_t piece, player_type player_type);

    bool move_is_legal(uint64_t source, uint64_t dest, uint8_t piece);

    std::optional<uint8_t> find_piece(uint64_t square);

    [[noreturn]] void fatal(const char* msg);

    // pieces[0..6] are whites pieces represented as a bitboard. Each 64 bit integer represents an
    // 8x8 board where each bit represents a presence flag for whether or not the square is
    // occupied. For example: pieces[0] are whites pawns where each bit tells us whether white has a
    // pawn on that square.
    std::array<uint64_t, 12> pieces;

    static constexpr std::array<std::string_view, 12> pieces_strings = {
        "P", "R", "N", "B", "K", "Q", "p", "r", "n", "b", "k", "q"};
};
