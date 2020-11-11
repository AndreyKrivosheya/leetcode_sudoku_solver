#include "sudoku.hpp"

#include "invalid_solution_error.hpp"

namespace leetcode { namespace sudoku_solver {
    int to_power_of_2_from_1_to_9(const short& value)
    {
        switch(value)
        {
            case 1 << (1 - 1):
                return 0;
            case 1 << (2 - 1):
                return 1;
            case 1 << (3 - 1):
                return 2;
            case 1 << (4 - 1):
                return 3;
            case 1 << (5 - 1):
                return 4;
            case 1 << (6 - 1):
                return 5;
            case 1 << (7 - 1):
                return 6;
            case 1 << (8 - 1):
                return 7;
            case 1 << (9 - 1):
                return 8;
            default:
                return -1;
        }
    }

    pair<int, int> first_not_last_candidate(const vector<vector<short>>& candidates)
    {
        auto first_not_last_candidate_row = -1;
        auto first_not_last_candidate_col = -1;
        for(auto i = 0; (first_not_last_candidate_row == -1 && first_not_last_candidate_col == -1) && (i < 9); i++)
        {
            for(auto j = 0; (first_not_last_candidate_row == -1 && first_not_last_candidate_col == -1) && (j < 9); j++)
            {
                if(candidates[i][j] == 0)
                {
                    throw invalid_solution_error();
                }
                else
                {
                    if(to_power_of_2_from_1_to_9(candidates[i][j]) == -1)
                    {
                        first_not_last_candidate_row = i;
                        first_not_last_candidate_col = j;
                    }
                }
            }
        }
        
        return {first_not_last_candidate_row, first_not_last_candidate_col};
    }

    void sudoku_signout_value(vector<vector<char>>& board, vector<vector<short>>& candidates, int row, int col)
    {
        auto value = board[row][col];
        auto value_index = value - '1';
        auto value_index_bit = 1 << value_index;
        
        candidates[row][col] = value_index_bit;
        // sign out all by row
        for(auto i = 0; i < 9; i++)
        {
            if(i != col)
            {
                if((candidates[row][i] & value_index_bit) != 0)
                {
                    candidates[row][i] &= ~value_index_bit;
                    // check last candidate
                    auto last_candidate = to_power_of_2_from_1_to_9(candidates[row][i]);
                    if(last_candidate != -1)
                    {
                        board[row][i] = '1' + last_candidate;
                        sudoku_signout_value(board, candidates, row, i);
                    }
                }
            }
        }
        // sign out all by column
        for(auto i = 0; i < 9; i++)
        {
            if(i != row)
            {
                if((candidates[i][col] & value_index_bit) != 0)
                {
                    candidates[i][col] &= ~value_index_bit;
                    // check last candidate
                    auto last_candidate = to_power_of_2_from_1_to_9(candidates[i][col]);
                    if(last_candidate != -1)
                    {
                        board[i][col] = '1' + last_candidate;
                        sudoku_signout_value(board, candidates, i, col);
                    }
                }
            }
        }
        // sign out all by 3x3 box
        for(auto i = (row - row % 3); i < ((row - row % 3) + 3); i++)
        {
            for(auto j = (col / 3) * 3; j < (col / 3) * 3 + 3; j++)
            {
                if(i != row || j != col)
                {
                    if((candidates[i][j] & value_index_bit) != 0)
                    {
                        candidates[i][j] &= ~value_index_bit;
                        // check last candidate
                        auto last_candidate = to_power_of_2_from_1_to_9(candidates[i][j]);
                        if(last_candidate != -1)
                        {
                            board[i][j] = '1' + last_candidate;
                            sudoku_signout_value(board, candidates, i, j);
                        }
                    }
                }
            }
        }
    }
    
    bool sudoku_solve(vector<vector<char>>& board, vector<vector<short>>& candidates)
    {
        // first, check signout is required
        if(first_not_last_candidate(candidates) == pair<int, int>({-1, -1}))
        {
            return true;
        }
        // second, signout all candidates that are present only in once cell in a row/column/box
        for(auto i = 0; i < 9; i++)
        {
            for(auto j = 0; j < 9; j++)
            {
                auto last_candidate = to_power_of_2_from_1_to_9(candidates[i][j]);
                if(last_candidate == -1)
                {
                    for(auto c = 0; c < 9; c++)
                    {
                        if((candidates[i][j] & (1 << c)) != 0)
                        {
                            // check that only candidates[i][j] has c as candidate
                            // ... check through row columns
                            auto row_only_value = true;
                            for(auto l = 0; l < 9; l++)
                            {
                                if(l != j)
                                {
                                    if((candidates[i][l] & (1 << c)) != 0)
                                    {
                                        row_only_value = false;
                                        break;
                                    }
                                }
                            }
                            if(row_only_value)
                            {
                                board[i][j] = '1' + c;
                                sudoku_signout_value(board, candidates, i, j);
                                // restart
                                i = -1;
                                j = 9;
                                c = 9;
                                continue;
                            }
                            // ... check through column rows
                            auto column_only_value = true;
                            for(auto l = 0; column_only_value && (l < 9); l++)
                            {
                                if(l != i)
                                {
                                    if((candidates[l][j] & (1 << c)) != 0)
                                    {
                                        column_only_value = false;
                                    }
                                }
                            }
                            if(column_only_value)
                            {
                                board[i][j] = '1' + c;
                                sudoku_signout_value(board, candidates, i, j);
                                // restart
                                i = -1;
                                j = 9;
                                c = 9;
                                continue;
                            }
                            // ... check through 3x3 box
                            auto box_only_value = true;
                            for(auto l = (i / 3) * 3; box_only_value && (l < (i / 3) * 3 + 3); l++)
                            {
                                for(auto m = (j / 3) * 3; box_only_value && (m < (j / 3) * 3 + 3); m++)
                                {
                                    if(l != i || m != j)
                                    {
                                        if((candidates[l][m] & (1 << c)) != 0)
                                        {
                                            box_only_value = false;
                                        }
                                    }
                                }
                            }
                            if(box_only_value)
                            {
                                board[i][j] = '1' + c;
                                sudoku_signout_value(board, candidates, i, j);
                                // restart
                                c = 9;
                                j = 9;
                                i = -1;
                                continue;
                            }
                        }
                    }
                }
            }
        }
        // third, find first not last candidate
        auto first_not_last_candidate_pair = first_not_last_candidate(candidates);
        if(first_not_last_candidate_pair == pair<int, int>({-1, -1}))
        {
            return true;
        }
        else
        {
            auto first_not_last_candidate_row = first_not_last_candidate_pair.first;
            auto first_not_last_candidate_col = first_not_last_candidate_pair.second;
            // forth, brut force through possible candidates
            for(auto k = 0; k < 9; k++)
            {
                if((candidates[first_not_last_candidate_row][first_not_last_candidate_col] & (1 << k)) != 0)
                {
                    vector<vector<char>> board_copy(board);
                    vector<vector<short>> candidates_copy(candidates);
                    // first, signout candidate
                    board_copy[first_not_last_candidate_row][first_not_last_candidate_col] = '1' + k;
                    sudoku_signout_value(board_copy, candidates_copy, first_not_last_candidate_row, first_not_last_candidate_col);
                    // second, try solving the rest
                    try
                    {
                        if(sudoku_solve(board_copy, candidates_copy))
                        {
                            board = board_copy;
                            candidates = candidates_copy;
                            return true;
                        }
                    }
                    catch(invalid_solution_error&)
                    {
                        continue;
                    }
                }
            }

            return false;
        }
    }

    bool sudoku::solve()
    {
        vector<vector<short>> candidates(9);
        for(auto i = 0; i < 9; i++)
        {
            candidates[i] = vector<short>(9, 0x01ff);
        }

        // first, sign out all values that are defined by input        
        for(auto i = 0; i < 9; i++)
        {
            for(auto j = 0; j < 9; j++)
            {
                if(board[i][j] != '.')
                {
                    sudoku_signout_value(board, candidates, i, j);
                }
            }
        }
        // second, sign out all candidates that are present only in one cell in a row/column/box
        // third, brut force through rest of candidates yet unsigned out
        try
        {
            return sudoku_solve(board, candidates);
        }
        catch(invalid_solution_error&)
        {
            return false;
        }
    }
} }