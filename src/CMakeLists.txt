set(SOURCES
    main.cc
    chess_board.cc)

add_executable(${PROJECT} ${SOURCES})
target_include_directories(${PROJECT} PRIVATE inc)
set_target_properties(${PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
