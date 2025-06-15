#ifndef UTIL_H
#define UTIL_H

int isValid(int board[9][9], int row, int col, int num);
int checkRow(int board[9][9], int row, int num);
int checkCol(int board[9][9], int col, int num);
int checkBox(int board[9][9], int startRow, int startCol, int num);

#endif
