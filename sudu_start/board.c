#include <stdio.h>
#include <windows.h>
#include "board.h"
#include "rlutil.h"

static void setConsoleEncoding() {
    SetConsoleOutputCP(65001);
}

void printBoard(int board[9][9]) {
    setConsoleEncoding();
    setColor(CYAN);
    printf("   1 2 3   4 5 6   7 8 9\n");
    for(int i = 0; i < 9; i++) {
        if(i % 3 == 0) {
            setColor(YELLOW);
            printf("   ---------------------\n");
        }
        setColor(CYAN);
        printf("%d |", i + 1);
        for(int j = 0; j < 9; j++) {
            if(j % 3 == 0 && j != 0) {
                setColor(YELLOW);
                printf("|");
            }
            if(board[i][j] == 0) {
                setColor(GREY);
                printf(" .");
            } else {
                setColor(GREEN);
                printf(" %d", board[i][j]);
            }
        }
        setColor(CYAN);
        printf(" |\n");
    }
    setColor(YELLOW);
    printf("   ---------------------\n");
    resetColor();
}

void initBoard(int board[9][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            board[i][j] = 0;
        }
    }
}
