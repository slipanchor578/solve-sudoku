#include "sudoku.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main() {

    std::string file_data;
    std::string line;

    #ifdef DEBUG
        std::ifstream f_stream("sudoku.txt");
        auto* cinbuf = std::cin.rdbuf(f_stream.rdbuf());
    #endif
    while (std::getline(std::cin, line)) {
        file_data += line;
    }

    if (file_data.empty()) {
        std::cerr << "入力データが無いので計算できません。" << std::endl;
        #ifdef DEBUG
            std::cin.rdbuf(cinbuf);
        #endif

        return 1;
    }

    SudokuSolver solver{file_data};

    if (solver.solve()) {
        std::cout << "Solved Sudoku:\n";
        solver.print();
    } else {
        std::cout << "No solution exists.\n";
    }

    std::cout << "Backtack count: " << solver.get_backtrack_count() << std::endl;
    #ifdef DEBUG
        std::cin.rdbuf(cinbuf);
    #endif

    return 0;
}