#include <stdio.h>
#include "ref/rlutil.h"

#define SIZE 9

extern int board[SIZE][SIZE];
extern int solution[SIZE][SIZE];
extern int cursorRow, cursorCol;

// Original board for checking if number is given or user-filled
int originalBoard[SIZE][SIZE] = {
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

// Function to print the Sudoku board with colors
void printBoard() {
    printf("\n    1 2 3   4 5 6   7 8 9\n");
    printf("  +-------+-------+-------+\n");
    
    for (int i = 0; i < SIZE; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < SIZE; j++) {
            // Set background color for current cursor position
            if (j==0) {
                setBackgroundColor(BLACK);
                setColor(WHITE);
                printf(" ");
            }
            if (i == cursorRow && j == cursorCol) {
                setBackgroundColor(YELLOW);
                setColor(BLACK);
            } else {
                setBackgroundColor(BLACK);
            }
            
            if (board[i][j] == 0) {
                setColor(GREY);
                if (j==0) printf(".");
                else printf(" .");
            } else {
                // Color coding: original numbers in white, user input in different colors
                if (originalBoard[i][j] != 0) {
                    setColor(WHITE);  // Original given numbers
                } else if (board[i][j] == solution[i][j]) {
                    setColor(GREEN);  // Correct user input
                } else {
                    setColor(RED);    // Incorrect user input
                }
                if (j==0) printf("%d", board[i][j]);
                else printf(" %d", board[i][j]);
            }
            
            // Reset colors
            setBackgroundColor(BLACK);
            setColor(WHITE);
            
            if ((j + 1) % 3 == 0) {
                printf(" |");
            }
        }
        printf("\n");
        if ((i + 1) % 3 == 0) {
            printf("  +-------+-------+-------+\n");
        }
    }
    printf("\n");
}
