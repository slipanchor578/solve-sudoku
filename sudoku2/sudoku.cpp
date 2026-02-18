#include "sudoku.hpp"
#include <algorithm>
#include <stdbool.h>

SudokuSolver::SudokuSolver(const std::string& data) {
    int count = 0;

    for (const char ch : data) {
        // 9x9=81マスなので0-80までとなる。81になったら抜ける
        if (count >= 81) break;
        // 数字ならそのまま変換。配列の配列で数独データを保持していたが
        // 一次元配列に変更したので、countをそのままインデックスとして使うように変更
        // 例えばgrid_[count = 9] = grid_[1][0] となり、二行目の最初のマスに対応している
        if (std::isdigit(static_cast<unsigned char>(ch))) grid_[count] = ch - '0';
        // ドットなら空白マスとして0を入れる
        else if (ch == '.') grid_[count] = 0;
        // 改行やタブの時はスルー
        else continue;
        ++count;
    }
}

bool SudokuSolver::is_valid(int pos, int val) const {
    // セル番号から行列番号を生成するように変更
    // 例えば一番左上のマスの場合、pos = 0 となり、(r, c) = (0, 0) となり変更前と同じになる
    int r = pos / 9;
    int c = pos % 9;
    for (int i = 0; i < 9; ++i) {
        // 行列に同じ数字が無いか確認
        // 一度にチェックするセルが所属する行と列を確認。もし1を置こうとして、どこかに1が既に置かれていたら
        // false を返す
        // r = 0 の時grid_は[0, 1, 2, 3, ... 8] となり行チェックできる
        // c = 0 の時grid_は[0, 9, 18, ... 72] となり列チェックできる
        if (grid_[r * 9 + i] == val || grid_[i * 9 + c] == val) return false;
    }

    // セル番号が所属する小グリッドの左上のセル番号を生成
    // 0-2(1-3)行目の場合は0、3-5(4-6)行目の場合は3、6-8(7-9)行目の場合は6となる
    int rs = (r / 3) * 3;
    // 0-2(1-3)列目の場合は0、3-5(4-6)列目の場合は3、6-8(7-9)列目の場合は6となる
    int cs = (c / 3) * 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            // 小グリッドに同じ数字が無いか確認
            // 二次元インデックスから一次元インデックスへの変換は(行番号 * 1列の要素数 + 列番号) となる
            // 最終セルであれば80なので二次元の時はarr[8][8] だったのが「8 * 9 + 8 = 80」 となりarr[80] でアクセスできる
            // 今回は小グリッドの3x3の範囲を確認したいので、rsにiを足すことで(rs + i) = (0, 1, 2) * 9 = (0, 9, 18) となり
            // 同じ列の次の行のセルの行番号を取得できる。列も左上セルを含めて3列確認したいので、(cs + j) = (0, 1, 2) となり
            // 隣の列番号を取得できる
            // これを変換式に入れると
            // (0, 0)(0, 1)(0, 2)
            // (1, 0)(1, 1)(1, 2)
            // (2, 0)(2, 1)(2, 2)
            // となり、左上セルを起点に小グリッドの全てのセルを確認できる
            if (grid_[(rs + i) * 9 + (cs + j)] == val) return false;
        }
    }
    return true;
}

bool SudokuSolver::solve_recursive(int p) {
    if (p == 81) return true;

    // 一次元配列になったので単にセル番号を入れるだけでいい
    if (grid_[p] != 0) return solve_recursive(p + 1);

    for (int val = 1; val <= 9; ++val) {
        // チェックしてから入れるように変更。前は入れてからチェックしていたので、明らかに隣マスに
        // 「1」が入っていても「1」を入れて無駄にチェックしていた
        if (is_valid(p, val)) {
            grid_[p] = val;
            if (solve_recursive(p + 1)) {
                return true;
            }
        }
    }

    // 駄目な時は0に戻して1マス戻る
    grid_[p] = 0;
    ++backtrack_count_;
    return false;
}

bool SudokuSolver::solve() {
    return solve_recursive(0);
}

void SudokuSolver::print() const {
    // ループは一巡でよい。インデックスはハードコーティングしない
    for (std::size_t i = 0; i < grid_.size(); ++i) {
        // 1行表示したら改行
        std::cout << grid_[i] << (i % 9 == 8 ? "\n" : " ");
    }
}