set(SOURCES
    main.cc
)

add_executable(${PROJECT} ${SOURCES})
target_include_directories(${PROJECT} PRIVATE inc)
target_link_libraries(${PROJECT} ${LIB_PROJECT})
set_target_properties(${PROJECT}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
