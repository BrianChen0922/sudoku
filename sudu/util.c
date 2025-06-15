#include <stdio.h>
#include <stdbool.h>
#include "ref/rlutil.h"

#define SIZE 9

extern int board[SIZE][SIZE];
extern int solution[SIZE][SIZE];

// Check if placing num at grid[row][col] is valid (for any grid)
bool isValidForGrid(int grid[SIZE][SIZE], int row, int col, int num) {
    // Check row
    for (int x = 0; x < SIZE; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }
    
    // Check column
    for (int x = 0; x < SIZE; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }
    
    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    
    return true;
}

// Solve Sudoku using backtracking
bool solveSudoku(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValidForGrid(grid, row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku(grid)) {
                            return true;
                        }
                        grid[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Check if placing num at board[row][col] is valid
bool isValid(int row, int col, int num) {
    return isValidForGrid(board, row, col, num);
}

// Check if the board is completely filled
bool isBoardFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

// Make a move (updated for new interface)
bool makeMove(int row, int col, int num) {
    if (row < 1 || row > 9 || col < 1 || col > 9) {
        return false;
    }
    
    row--; // Convert to 0-based indexing
    col--;
    
    if (board[row][col] != 0) {
        // Allow overwriting user input
        // Check if it's an original given number
        extern int originalBoard[SIZE][SIZE];
        if (originalBoard[row][col] != 0) {
            return false; // Cannot overwrite original numbers
        }
    }
    
    if (num < 1 || num > 9) {
        return false;
    }
    
    if (!isValid(row, col, num)) {
        return false;
    }
    
    board[row][col] = num;
    return true;
}
