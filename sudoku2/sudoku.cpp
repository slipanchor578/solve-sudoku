#include "sudoku.hpp"
#include <algorithm>
#include <stdbool.h>

SudokuSolver::SudokuSolver(const std::string& data) {
    int count = 0;

    for (const char ch : data) {
        // 9x9=81マスなので0-80までとなる。81になったら抜ける
        if (count >= 81) break;
        // 数字ならそのまま変換。count = 9 = 2行目に突入したらgrid_[1][0] となり適応できている
        if (std::isdigit(ch)) grid_[count / 9][count % 9] = ch - '0';
        // ドットなら空白マスとして0を入れる
        else if (ch == '.') grid_[count / 9][count % 9] = 0;
        // 改行やタブの時はスルー
        else continue;
        ++count;
    }
}

bool SudokuSolver::is_valid(int r, int c, int val) const {
    for (int i = 0; i < 9; ++i) {
        // 行列に同じ数字が無いか確認
        if (grid_[r][i] == val || grid_[i][c] == val) return false;
    }

    // 例えば(r, c) = (8, 8) の最終マスの場合、(rs, cs) = (6, 6) となり、右下グリッドの左上マスを取得する
    int rs = (r / 3) * 3;
    int cs = (c / 3) * 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            // 小グリッドに同じ数字が無いか確認
            if (grid_[rs + i][cs + j] == val) return false;
        }
    }
    return true;
}

bool SudokuSolver::solve_recursive(int p) {
    if (p == 81) return true;

    int r = p / 9;
    int c = p % 9;

    if (grid_[r][c] != 0) return solve_recursive(p + 1);

    for (int val = 1; val <= 9; ++val) {
        // チェックしてから入れる。前は入れてからチェックしていたので、隣に1が入っていても1を入れていた
        if (is_valid(r, c, val)) {
            grid_[r][c] = val;
            if (solve_recursive(p + 1)) {
                return true;
            }
        }
    }

    // 駄目な時は0に戻して1マス戻る
    grid_[r][c] = 0;
    ++backtrack_count_;
    return false;
}

bool SudokuSolver::solve() {

    return solve_recursive(0);
}

void SudokuSolver::print() const {
    for (const auto& row : grid_) {
        for (int i = 0; i < 9; ++i) {
            std::cout << row[i] << (i == 8 ? "" : " ");
        }
        std::cout << '\n';
    }
}