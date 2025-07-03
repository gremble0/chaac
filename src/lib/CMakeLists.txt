set(SOURCES
    chess_board.cc
)
set(LIB_PROJECT lib-${PROJECT})

add_library(${LIB_PROJECT} ${SOURCES})
target_include_directories(${LIB_PROJECT} PRIVATE inc)
set_target_properties(${LIB_PROJECT}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
