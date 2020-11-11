cmake_minimum_required(VERSION 3.18)
include(GoogleTest)

set(This sudoku_solver_tests)

set(Headers
)

set(Sources
    sudoku/solve/tests__should.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC "-static"
    gmock
    gtest_main

    sudoku_solver
)

gtest_discover_tests(${This})
