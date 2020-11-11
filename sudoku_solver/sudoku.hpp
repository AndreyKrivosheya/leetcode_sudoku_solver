#pragma once
#include <vector>

using namespace std;

namespace leetcode { namespace sudoku_solver {
    class sudoku
    {
        public:

        sudoku(const vector<vector<char>>& board)
            : board(board)
        {
        }

        vector<vector<char>> get_board()
        {
            return board;
        }

        private:

        vector<vector<char>> board;

        //////////////////////////////////////////////////////////////////////////////////////
        // solve implementation
        //////////////////////////////////////////////////////////////////////////////////////
        
        public:

        bool solve();
    };
} }