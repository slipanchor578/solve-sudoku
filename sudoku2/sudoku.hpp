#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <array>
#include <iostream>
#include <string>
#include <vector>

class SudokuSolver {
    public:
        using Grid = std::array<std::array<int, 9>, 9>;

        explicit SudokuSolver(const std::string& data);
        bool solve();
        void print() const;
        size_t get_backtrack_count() const { return backtrack_count_; }

    private:
        Grid grid_{};
        size_t backtrack_count_ = 0;

        bool is_valid(int r, int c, int val) const;
        bool solve_recursive(int p);
};

#endif // SUDOKU_HPP