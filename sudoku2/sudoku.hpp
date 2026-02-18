#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <array>
#include <iostream>
#include <string>
#include <vector>

class SudokuSolver {
    public:
        // これまで9x9の数独を表現するため二次元配列で持っていたのを一次元配列に変更
        using Grid = std::array<int, 81>;

        explicit SudokuSolver(const std::string& data);
        bool solve();
        void print() const;
        size_t get_backtrack_count() const { return backtrack_count_; }

    private:
        Grid grid_{};
        size_t backtrack_count_ = 0;

        // マス目番号posから行列番号(r, c)を生成するように変更
        bool is_valid(int pos, int val) const;
        bool solve_recursive(int p);
};

#endif // SUDOKU_HPP