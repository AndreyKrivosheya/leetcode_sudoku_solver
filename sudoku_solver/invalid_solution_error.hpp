#pragma once
#include <stdexcept>

using namespace std;

namespace leetcode { namespace sudoku_solver {
    class invalid_solution_error : runtime_error
    {
        public:

        invalid_solution_error()
            : runtime_error("Invalid solution")
        {
        }
    };
}}