set(TESTS
  test_chess_board.cc
  test_chess_move.cc
  test_chess_notation.cc
)

find_package(Catch2 3 REQUIRED)
add_executable(test ${TESTS})
target_link_libraries(test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test PRIVATE ${LIB_PROJECT})
