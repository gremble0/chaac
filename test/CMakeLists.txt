# External libraries
find_package(Catch2 3 REQUIRED)
add_executable(test test_chess_board.cc)
target_link_libraries(test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test PRIVATE ${LIB_PROJECT})
