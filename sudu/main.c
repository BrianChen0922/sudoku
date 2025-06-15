#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ref/rlutil.h"

#define SIZE 9

// Function declarations
void printBoard();
bool isValidForGrid(int grid[SIZE][SIZE], int row, int col, int num);
bool solveSudoku(int grid[SIZE][SIZE]);
bool isValid(int row, int col, int num);
bool isBoardFull();
bool makeMove(int row, int col, int num);

// Global Sudoku board
int board[SIZE][SIZE] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

// Solution board
int solution[SIZE][SIZE];

// Cursor position (0-based)
int cursorRow = 0;
int cursorCol = 0;

// rlutil wrapper functions to be called from other files
void setColorWrapper(int color) {
    setColor(color);
}

void setBackgroundColorWrapper(int color) {
    setBackgroundColor(color);
}

int main() {
    cls();
    printf("=== SUDOKU GAME ===\n");
    printf("Calculating solution...\n");
    
    // Copy the original board to solution and solve it
    memcpy(solution, board, sizeof(board));
    if (!solveSudoku(solution)) {
        printf("Error: Unable to solve this Sudoku puzzle!\n");
        return 1;
    }
    
    printf("Solution calculated! Game ready.\n");
    printf("Use arrow keys to navigate, 1-9 to fill numbers, ESC to quit.\n");
    printf("Press any key to start...\n");
    getch();
    
    cls();
    printBoard();
    printf("Position: Row %d, Col %d\n", cursorRow + 1, cursorCol + 1);
    printf("Use arrow keys to move, 1-9 to enter number, ESC to quit\n");
    
    while (true) {
        if (isBoardFull()) {
            gotoxy(1, 17);
            printf("Congratulations! You solved the Sudoku!\n");
            printf("Press any key to exit...\n");
            getch();
            break;
        }
        
        // Check if key is pressed before reading
        if (kbhit()) {
            int key = getch();
            
            // Handle arrow keys (check for special key sequence)
            if (key == 0 || key == 224) { // Special key prefix
                key = getch(); // Get the actual arrow key code
                int oldRow = cursorRow, oldCol = cursorCol;
                switch (key) {
                    case 72: // Up arrow
                        if (cursorRow > 0) cursorRow--;
                        break;
                    case 80: // Down arrow
                        if (cursorRow < SIZE - 1) cursorRow++;
                        break;
                    case 75: // Left arrow
                        if (cursorCol > 0) cursorCol--;
                        break;
                    case 77: // Right arrow
                        if (cursorCol < SIZE - 1) cursorCol++;
                        break;
                }
                // Update only the changed cells and position info
                if (oldRow != cursorRow || oldCol != cursorCol) {
                    // Redraw old position
                    int oldX = 5 + oldCol * 2 + 2*(oldCol / 3);
                    int oldY = 3 + oldRow + (oldRow / 3) + 1;
                    gotoxy(oldX, oldY);
                    setBackgroundColor(BLACK);
                    if (board[oldRow][oldCol] == 0) {
                        setColor(GREY);
                        printf(".");
                    } else {
                        // Color based on original/correct/incorrect
                        extern int originalBoard[SIZE][SIZE];
                        if (originalBoard[oldRow][oldCol] != 0) {
                            setColor(WHITE);  // Original given numbers
                        } else if (board[oldRow][oldCol] == solution[oldRow][oldCol]) {
                            setColor(GREEN);  // Correct user input
                        } else {
                            setColor(RED);    // Incorrect user input
                        }
                        printf("%d", board[oldRow][oldCol]);
                    }
                    
                    // Draw new cursor position
                    int newX = 5 + cursorCol * 2 + 2*(cursorCol / 3);
                    int newY = 3 + cursorRow + (cursorRow / 3) + 1;
                    gotoxy(newX, newY);
                    setBackgroundColor(YELLOW);
                    setColor(BLACK);
                    if (board[cursorRow][cursorCol] == 0) {
                        printf(".");
                    } else {
                        printf("%d", board[cursorRow][cursorCol]);
                    }
                    setBackgroundColor(BLACK);
                    setColor(WHITE);
                    
                    // Update position info
                    gotoxy(1, 17);
                    printf("Position: Row %d, Col %d", cursorRow + 1, cursorCol + 1);
                }
            }
            // Handle number input
            else if (key >= '1' && key <= '9') {
                int num = key - '0';
                if (makeMove(cursorRow + 1, cursorCol + 1, num)) {
                    // Update only the current cell
                    int newX = 5 + cursorCol * 2 + 2*(cursorCol / 3);
                    int newY = 3 + cursorRow + (cursorRow / 3) + 1;
                    gotoxy(newX, newY);
                    setBackgroundColor(YELLOW);
                    
                    // Set color based on correctness
                    if (board[cursorRow][cursorCol] == solution[cursorRow][cursorCol]) {
                        setColor(GREEN);  // Correct answer
                    } else {
                        setColor(RED);    // Incorrect answer
                    }
                    
                    printf("%d", num);
                    setBackgroundColor(BLACK);
                    setColor(WHITE);
                }
            }
            // Handle ESC key
            else if (key == 27) { // ESC key
                gotoxy(1, 17);
                printf("Thanks for playing!\n");
                break;
            }
        }
    }
    
    return 0;
}
