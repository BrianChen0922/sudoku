#include <stdio.h>
#include <windows.h>

// 數獨盤面結構
typedef struct {
    int numbers;   // 檔案中的問題總數
    int datasize;  // 每個問題的資料大小（位元組）
} SudokuDataHeader;

typedef struct {
    int id;         // 問題編號
    int data[9][9]; // 盤面資料
} SudokuProblem;

// 初始數獨盤面
int board[9][9] = {
    {0, 0, 0, 0, 0, 0, 0, 9, 0},
    {1, 9, 0, 4, 7, 0, 6, 0, 8},
    {0, 5, 2, 8, 1, 9, 4, 0, 7},
    {2, 0, 0, 0, 4, 8, 0, 0, 0},
    {0, 0, 9, 0, 0, 0, 5, 0, 0},
    {0, 0, 0, 7, 5, 0, 0, 0, 9},
    {9, 0, 7, 3, 6, 4, 1, 8, 0},
    {5, 0, 6, 0, 8, 1, 0, 7, 4},
    {0, 8, 0, 0, 0, 0, 0, 0, 0}
};

// 遊戲用全域變數
int player_board[9][9];     // 玩家當前的盤面
int answer_board[9][9];     // 正確答案盤面
int original_board[9][9];   // 原始問題盤面
int error_count = 0;        // 錯誤計數

// 函數原型宣告
void print_board(int board[][9]);
void save_to_text_file(int board[][9], const char* filename);
int read_from_text_file(int board[][9], const char* filename);
void save_to_binary_file(int board[][9], int problem_id, const char* filename, int is_append);
int read_from_binary_file(int board[][9], const char* filename, int problem_index);
int isValid(int number, int puzzle[][9], int row, int col);
int solve(int puzzle[][9], int pos);
void init_game();
int handle_input();
int is_complete();
void play_game();
static void setConsoleEncoding();

// 主函數
int main() {
    setConsoleEncoding();
    play_game();
    return 0;
}

// 設定編碼
static void setConsoleEncoding() {
    system("chcp 65001 > nul");    // 設定為 UTF-8
    SetConsoleOutputCP(65001);      // 設定輸出編碼
    SetConsoleCP(65001);           // 設定輸入編碼
}

// 輸出格式化的數獨盤面
void print_board(int board[][9]) {
    printf("\n +-------+-------+-------+\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) printf(" | ");
            else printf(" ");
            
            if (board[i][j] == 0) {
                printf("_");
            } else {
                printf("%d", board[i][j]);
            }
        }
        printf(" |\n");
        if (i % 3 == 2) printf(" +-------+-------+-------+\n");
    }
}

// 檢查數字是否有效
int isValid(int number, int puzzle[][9], int row, int col) {
    int rowStart = (row / 3) * 3;
    int colStart = (col / 3) * 3;
    
    for (int i = 0; i < 9; i++) {
        if (puzzle[row][i] == number) return 0;
        if (puzzle[i][col] == number) return 0;
        if (puzzle[rowStart + (i / 3)][colStart + (i % 3)] == number) return 0;
    }
    
    return 1;
}

// 遞迴解題函數
int solve(int puzzle[][9], int pos) {
    if (pos == 81) return 1;
    
    int row = pos / 9;
    int col = pos % 9;
    
    if (puzzle[row][col] != 0) {
        return solve(puzzle, pos + 1);
    }
    
    for (int num = 1; num <= 9; num++) {
        if (isValid(num, puzzle, row, col)) {
            puzzle[row][col] = num;
            if (solve(puzzle, pos + 1)) return 1;
        }
    }
    
    puzzle[row][col] = 0;
    return 0;
}

// 遊戲初始化
void init_game() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            original_board[i][j] = board[i][j];
            player_board[i][j] = board[i][j];
            answer_board[i][j] = board[i][j];
        }
    }
    
    solve(answer_board, 0);
    error_count = 0;
    
    printf("遊戲初始化完成！\n");
}

// 處理玩家輸入
int handle_input() {
    int row, col, num;
    
    printf("請輸入 行 列 數字 (1-9)，或輸入 0 0 0 結束遊戲: ");
    scanf("%d %d %d", &row, &col, &num);
    
    if (row == 0 && col == 0 && num == 0) {
        return -1;
    }
    
    if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
        printf("輸入超出範圍！請輸入 1-9 之間的數字。\n");
        return 0;
    }
    
    row--; col--;
    
    if (original_board[row][col] != 0) {
        printf("該位置是原始數字，不能修改！\n");
        return 0;
    }
    
    if (player_board[row][col] != 0) {
        printf("該位置已經填過數字了！\n");
        return 0;
    }
    
    if (answer_board[row][col] == num) {
        player_board[row][col] = num;
        printf("正確！\n");
        return 1;
    } else {
        error_count++;
        printf("錯誤！錯誤次數：%d\n", error_count);
        return 1;
    }
}

// 檢查遊戲是否完成
int is_complete() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (player_board[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

// 遊戲主迴圈
void play_game() {
    printf("=== 數獨遊戲 ===\n");
    printf("規則：輸入 行 列 數字 來填數字\n");
    printf("錯誤5次遊戲結束\n\n");
    
    init_game();
    
    printf("初始盤面：\n");
    print_board(player_board);
    
    while (error_count < 5) {
        int result = handle_input();
        
        if (result == -1) {
            printf("遊戲結束！\n");
            break;
        }
        
        if (result == 1) {
            printf("\n當前盤面：\n");
            print_board(player_board);
            
            if (is_complete()) {
                printf("🎉 恭喜！你完成了數獨！\n");
                break;
            }
        }
    }
    
    if (error_count >= 5) {
        printf("💥 錯誤太多次，遊戲結束！\n");
        printf("正確答案：\n");
        print_board(answer_board);
    }
}
