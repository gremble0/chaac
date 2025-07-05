set(SOURCES
    board.cc
    input.cc
)

add_library(${LIB_PROJECT} ${SOURCES})
target_include_directories(${LIB_PROJECT} PUBLIC inc)
