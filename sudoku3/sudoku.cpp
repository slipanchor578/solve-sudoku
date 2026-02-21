#include "sudoku.hpp"
#include <algorithm>
#include <vector>

SudokuSolver::SudokuSolver(const std::string& data) {
    int count = 0;

    for (const char ch : data) {
        if (count >= 81) break;
        if (std::isdigit(static_cast<unsigned char>(ch))) grid_[count] = ch - '0';
        else if (ch == '.') grid_[count] = 0;
        else continue;
        ++count;
    }
}

bool SudokuSolver::is_valid(int pos, int val) const {
    int r = pos / 9;
    int c = pos % 9;
    for (int i = 0; i < 9; ++i) {
        if (grid_[r * 9 + i] == val || grid_[i * 9 + c] == val) return false;
    }
    int rs = (r / 3) * 3;
    int cs = (c / 3) * 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid_[(rs + i) * 9 + (cs + j)] == val) return false;
        }
    }
    return true;
}

bool SudokuSolver::solve_recursive() {

    // 空白マスの場所と、そこに置ける数字の情報が貯めていく
    std::vector<CellInfo> empty_cells;

    for (int i = 0; i < 81; ++i) {
        if (grid_[i] == 0) {
            CellInfo cell;
            cell.index = i;

            // 1-9 の中で置ける数字をリストアップ
            for (int val = 1; val <= 9; ++val) {
                if (is_valid(i, val)) {
                    cell.candidates.push_back(val);
                }
            }
            // 貯めていく
            empty_cells.push_back(std::move(cell));
        }
    }

    // 空きマスが無ければ成功(終了)
    // 明らかに候補が無い時に即座に戻る
    if (empty_cells.empty()) return true;

    // 候補数が少ない順に並び替え。つまり空マスのうち、入力候補が少ない入力しやすい
    // 場所から入力していくようにする
    std::sort(empty_cells.begin(), empty_cells.end(), [](const auto& a, const auto& b) {
        return a.candidates.size() < b.candidates.size();
    });

    // 最も候補が少ないマスを取り出し
    const auto& target = empty_cells.front();

    // もし候補が0なら戻る。0ということは置ける数字がないので失敗
    if (target.candidates.empty()) {
        ++backtrack_count_;
        return false;
    }

    // 入力していく
    for (const auto& val : target.candidates) {

        // 前は入力してからチェック、あるいはチェックしてから入力していたが
        // ここに来るまでに入力できる可能性のある数字をリストアップしているので、とりあえず入れたらいい
        grid_[target.index] = val;
        // 次のマスへ
        if (solve_recursive()) {
            return true;
        }

        // 失敗したのでリセット
        grid_[target.index] = 0;
    }

    ++backtrack_count_;
    // 候補自体はあったが、どれを試しても駄目だったので戻る
    return false;
}

bool SudokuSolver::solve() {
    return solve_recursive();
}

void SudokuSolver::print() const {
    int count = 0;
    for (const auto& num: grid_) {
        std::cout << num;
        count++;
        if (count % 9 == 0) std::cout << " ";
    }
    std::cout << "\n";
}