#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <array>
#include <iostream>
#include <string>
#include <vector>

class SudokuSolver {
    public:
        using Grid = std::array<int, 81>;

        explicit SudokuSolver(const std::string& data);
        bool solve();
        void print() const;
        size_t get_backtrack_count() const { return backtrack_count_; }

    private:
        Grid grid_{};
        size_t backtrack_count_ = 0;
        bool is_valid(int pos, int val) const;
        // 内部で最適なマスを探すため引数 p が要らなくなった
        bool solve_recursive();

        // 空のマスと、そこに置ける可能性のある数字を保持する構造体を作成
        struct CellInfo {
            int index;
            std::vector<int> candidates;
        };
};

#endif // SUDOKU_HPP