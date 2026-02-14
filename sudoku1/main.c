#include "sudoku.h"

static void process_line_by_line(char* buffer, int buffer_size, char* reserve) {
    int j = 0;
    while (fgets(buffer, buffer_size, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        for (int i = 0; buffer[i] != '\0'; ++i) {
            if (!isspace(buffer[i])) {
                reserve[j++] = buffer[i];
            }
        }
        reserve[j] = '\0';
    }
}

void solve_sudoku() {
    char line[BUFFER_SIZE];
    char reserve[BUFFER_SIZE];
    int** arr;

    #ifdef DEBUG
        freopen("sudoku.txt", "r", stdin);
    #endif
    process_line_by_line(line, BUFFER_SIZE, reserve);

    arr = make_grid(reserve);
    if (solve(arr)) {
        printf("Solved Sudoku:\n");
        print_grid(arr);
    } else {
        printf("No solution exists.\n");
    }

    printf("Backtrack count: %lu\n", backtrack_count);

    free_grid(arr);
}

int main(void) {
    solve_sudoku();
    return 0;
}