#ifndef SUDOKU_H
#define SUDOKU_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
extern unsigned long backtrack_count;

void solve_sudoku(void);
int** make_grid(const char* data);
void free_grid(int** grid);
void print_grid(int** grid);
bool solve(int** grid);

#endif // SUDOKU_H