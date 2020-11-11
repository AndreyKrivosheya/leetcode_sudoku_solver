cmake_minimum_required(VERSION 3.18)

set(This sudoku_solver)

enable_testing()

set(Headers
    invalid_solution_error.hpp
    sudoku.hpp
)
set(Sources
    invalid_solution_error.cpp
    sudoku.cpp
)

add_library(${This} STATIC ${Sources} ${Headerss})
target_link_libraries(${This} PUBLIC
)

add_subdirectory(tests)