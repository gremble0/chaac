#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>

enum class player_type : uint8_t {
    WHITE,
    BLACK,
};

enum class piece_type : uint8_t {
    WHITE_PAWN,
    WHITE_ROOK,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_KING,
    WHITE_QUEEN,
    BLACK_PAWN,
    BLACK_ROOK,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_KING,
    BLACK_QUEEN,
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

    bool move_is_legal(uint64_t source, uint64_t dest, piece_type piece_type) const;
    bool move_is_legal_for_pawn(uint64_t source, uint64_t dest) const;
    bool move_is_legal_for_rook(uint64_t source, uint64_t dest) const;
    bool move_is_legal_for_knight(uint64_t source, uint64_t dest) const;
    bool move_is_legal_for_bishop(uint64_t source, uint64_t dest) const;
    bool move_is_legal_for_king(uint64_t source, uint64_t dest) const;
    bool move_is_legal_for_queen(uint64_t source, uint64_t dest) const;

    bool piece_is_ours(piece_type piece_type, player_type player_type) const;

    std::optional<piece_type> find_piece(uint64_t square) const;

    static constexpr std::size_t NUM_PIECES = 12;

    // pieces[0..6] are whites pieces represented as a bitboard. Each 64 bit integer represents an
    // 8x8 board where each bit represents a presence flag for whether or not the square is
    // occupied. For example: pieces[0] are whites pawns where each bit tells us whether white has a
    // pawn on that square.
    std::array<uint64_t, NUM_PIECES> pieces;

    static constexpr auto pieces_strings =
        std::to_array({"P", "R", "N", "B", "K", "Q", "p", "r", "n", "b", "k", "q"});
};
