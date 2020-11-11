#include <gmock\gmock.h>
#include <gtest\gtest.h>

#include "..\..\..\sudoku.hpp"

using namespace leetcode::sudoku_solver;
using namespace std;

using ::testing::ElementsAre;
using ::testing::ElementsAreArray;

namespace tests__leetcode__sudoku_solver__sudoku__solve {
    TEST(tests__leetcode__sudoku_solver__sudoku__solve, should_solve_simple)
    {
        auto sut = leetcode::sudoku_solver::sudoku(vector<vector<char>>({
            {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
        }));

        EXPECT_TRUE(sut.solve());
        ASSERT_THAT(sut.get_board(), ElementsAre(
            ElementsAreArray({'5', '3', '4', '6', '7', '8', '9', '1', '2'}),
            ElementsAreArray({'6', '7', '2', '1', '9', '5', '3', '4', '8'}),
            ElementsAreArray({'1', '9', '8', '3', '4', '2', '5', '6', '7'}),
            ElementsAreArray({'8', '5', '9', '7', '6', '1', '4', '2', '3'}),
            ElementsAreArray({'4', '2', '6', '8', '5', '3', '7', '9', '1'}),
            ElementsAreArray({'7', '1', '3', '9', '2', '4', '8', '5', '6'}),
            ElementsAreArray({'9', '6', '1', '5', '3', '7', '2', '8', '4'}),
            ElementsAreArray({'2', '8', '7', '4', '1', '9', '6', '3', '5'}),
            ElementsAreArray({'3', '4', '5', '2', '8', '6', '1', '7', '9'})
        ));
    }

    TEST(tests__leetcode__sudoku_solver__sudoku__solve, should_solve_hardcore)
    {
        auto sut = leetcode::sudoku_solver::sudoku(vector<vector<char>>({
            {'.', '.', '9', '7', '4', '8', '.', '.', '.'},
            {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
            {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
            {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
            {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
            {'.', '9', '8', '.', '.', '.', '3', '.', '.'},
            {'.', '.', '.', '8', '.', '3', '.', '2', '.'},
            {'.', '.', '.', '.', '.', '.', '.', '.', '6'},
            {'.', '.', '.', '2', '7', '5', '9', '.', '.'}
        }));

        EXPECT_TRUE(sut.solve());
        ASSERT_THAT(sut.get_board(), ElementsAre(
            ElementsAreArray({'5', '1', '9', '7', '4', '8', '6', '3', '2'}),
            ElementsAreArray({'7', '8', '3', '6', '5', '2', '4', '1', '9'}),
            ElementsAreArray({'4', '2', '6', '1', '3', '9', '8', '7', '5'}),
            ElementsAreArray({'3', '5', '7', '9', '8', '6', '2', '4', '1'}),
            ElementsAreArray({'2', '6', '4', '3', '1', '7', '5', '9', '8'}),
            ElementsAreArray({'1', '9', '8', '5', '2', '4', '3', '6', '7'}),
            ElementsAreArray({'9', '7', '5', '8', '6', '3', '1', '2', '4'}),
            ElementsAreArray({'8', '3', '2', '4', '9', '1', '7', '5', '6'}),
            ElementsAreArray({'6', '4', '1', '2', '7', '5', '9', '8', '3'})
        ));
    }
}