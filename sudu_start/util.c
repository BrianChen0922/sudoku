#include "util.h"

int isValid(int board[9][9], int row, int col, int num) {
    return !checkRow(board, row, num) && 
           !checkCol(board, col, num) && 
           !checkBox(board, row - row % 3, col - col % 3, num);
}

int checkRow(int board[9][9], int row, int num) {
    for(int col = 0; col < 9; col++) {
        if(board[row][col] == num) return 1;
    }
    return 0;
}

int checkCol(int board[9][9], int col, int num) {
    for(int row = 0; row < 9; row++) {
        if(board[row][col] == num) return 1;
    }
    return 0;
}

int checkBox(int board[9][9], int startRow, int startCol, int num) {
    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < 3; col++) {
            if(board[row + startRow][col + startCol] == num) return 1;
        }
    }
    return 0;
}
