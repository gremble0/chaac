set(SOURCES
    chess_board.cc
)

add_library(${LIB_PROJECT} ${SOURCES})
target_include_directories(${LIB_PROJECT} PUBLIC inc)
