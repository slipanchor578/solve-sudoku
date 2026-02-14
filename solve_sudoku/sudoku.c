#include "sudoku.h"

unsigned long backtrack_count = 0;

static bool block_is_ok(int block[9]) {
    bool used[10] = {false};
    for (int i = 0; i < 9; ++i) {
        int v = block[i];
        if (v == 0) continue;
        if (used[v]) return false;
        used[v] = true;
    }
    return true;
}

static bool no_violation(int** grid, int r, int c) {
    int block[9];

    if (!block_is_ok(grid[r])) return false;

    for (int i = 0; i < 9; ++i) block[i] = grid[i][c];
    if (!block_is_ok(block)) return false;

    int row_start = (r / 3) * 3;
    int col_start = (c / 3) * 3;
    for (int i = 0; i < 9; ++i) {
        block[i] = grid[row_start + (i / 3)][col_start + (i % 3)];
    }
    if (!block_is_ok(block)) return false;
    return true;
}

static bool solve_sub(int** grid, int p) {
    if (p > 80) return true;

    int i = p / 9;
    int j = p % 9;

    if (grid[i][j] != 0) return solve_sub(grid, p + 1);

    for (int v = 1; v <= 9; ++v) {
        grid[i][j] = v;
        if (no_violation(grid, i, j)) {
            if (solve_sub(grid, p + 1)) {
                return true;
            }
        }
    }

    grid[i][j] = 0;
    ++backtrack_count;
    return false;
}

bool solve(int** grid) {
    return solve_sub(grid, 0);
}

int** make_grid(const char* data) {
    int** grid = malloc(9 * sizeof(int*));

    for (int i = 0; i < 9; ++i) {
        grid[i] = malloc(9 * sizeof(int));

        for (int j = 0; j < 9; ++j) {
            char c = data[i * 9 + j];
            grid[i][j] = (c == '.') ? 0 : (c - '0');
        }
    }
    return grid;
}

void free_grid(int** arr) {
    for (int i = 0; i < 9; ++i) {
        free(arr[i]);
    }
    free(arr);
}

void print_grid(int** grid) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            printf("%d", grid[i][j]);
        }
        putchar('\n');
    }
}