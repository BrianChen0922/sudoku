#include<stdio.h> // 引入標準輸入輸出標頭檔

void print_board(int board[][9]) { // 印出數獨盤面的函式，參數為9x9整數陣列
    printf("\n +-------+-------+-------+\n"); // 印出上方邊框
    for (int i = 0; i < 9; i++) { // 逐列處理
        for (int j = 0; j < 9; j++) { // 逐行處理
            if (j % 3 == 0) printf(" | "); // 每三格加一條豎線分隔
            else printf(" "); // 其他格子間加空格

            if (board[i][j] == 0) {
                printf("_");  // 若該格為0，印底線表示空格
            } else {
                printf("%d", board[i][j]); // 否則印出該格的數字
            }
        }
        printf(" |\n"); // 每列結束加右側豎線並換行
        if (i % 3 == 2) printf(" +-------+-------+-------+\n"); // 每三列加一條橫線分隔
    }
}

// 預設的數獨盤面，0 代表空格
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

// ========== 新增區塊：遊戲用全域變數 ==========
// 說明：增加遊戲所需的基本變數
int player_board[9][9];     // 玩家當前的盤面
int answer_board[9][9];     // 正確答案盤面
int original_board[9][9];   // 原始問題盤面
int error_count = 0;        // 錯誤計數
// ========== 新增區塊：遊戲初始化函式 ==========
// 說明：準備遊戲所需的盤面和答案
void init_game() {
    // 複製原始問題到各個盤面
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            original_board[i][j] = board[i][j];
            player_board[i][j] = board[i][j];
            answer_board[i][j] = board[i][j];
        }
    }
    
    // 計算正確答案
    solve(answer_board, 0);
    
    // 重置錯誤計數
    error_count = 0;
    
    printf("遊戲初始化完成！\n");
}
// ========== 新增區塊：輸入處理函式 ==========
// 說明：處理玩家輸入並檢查答案
int handle_input() {
    int row, col, num;
    
    printf("請輸入 行 列 數字 (1-9)，或輸入 0 0 0 結束遊戲: ");
    scanf("%d %d %d", &row, &col, &num);
    
    // 檢查是否要結束遊戲
    if (row == 0 && col == 0 && num == 0) {
        return -1; // 結束遊戲
    }
    
    // 檢查輸入範圍
    if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
        printf("輸入超出範圍！請輸入 1-9 之間的數字。\n");
        return 0; // 繼續遊戲
    }
    
    // 轉換為陣列索引 (0-8)
    row--; col--;
    
    // 檢查該位置是否為原始數字
    if (original_board[row][col] != 0) {
        printf("該位置是原始數字，不能修改！\n");
        return 0;
    }
    
    // 檢查該位置是否已經填過
    if (player_board[row][col] != 0) {
        printf("該位置已經填過數字了！\n");
        return 0;
    }
    
    // 檢查答案是否正確
    if (answer_board[row][col] == num) {
        // 正確
        player_board[row][col] = num;
        printf("正確！\n");
        return 1;
    } else {
        // 錯誤
        error_count++;
        printf("錯誤！錯誤次數：%d\n", 
error_count);
        return 1;
    }
}
// ========== 新增區塊：遊戲完成檢查 ==========
// 說明：檢查是否完成遊戲
int is_complete() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (player_board[i][j] == 0) {
                return 0; // 還有空格
            }
        }
    }
    return 1; // 完成
}
// ========== 新增區塊：遊戲主函式 ==========
// 說明：遊戲的主要控制邏輯
void play_game() {
    printf("=== 數獨遊戲 ===\n");
    printf("規則：輸入 行 列 數字 來填數字\n");
    printf("錯誤5次遊戲結束\n\n");
    
    // 初始化遊戲
    init_game();
    
    // 顯示初始盤面
    printf("初始盤面：\n");
    print_board(player_board);
    
    // 遊戲主迴圈
    while (error_count < 5) {
        int result = handle_input();
        
        if (result == -1) {
            printf("遊戲結束！\n");
            break;
        }
        
        if (result == 1) {
            // 顯示當前盤面
            printf("\n當前盤面：\n");
            print_board(player_board);
            
            // 檢查是否完成
            if (is_complete()) {
                printf("🎉 恭喜！你完成了數獨！\n");
                break;
            }
        }
    }
    
    // 遊戲結束處理
    if (error_count >= 5) {
        printf("💥 錯誤太多次，遊戲結束！\n");
        printf("正確答案：\n");
        print_board(answer_board);
    }
}

void save_to_text_file(int board[][9], const char* filename) {
    FILE *fp = fopen(filename, "w"); // 以寫入模式開啟檔案
    if (fp == NULL) { // 檢查檔案是否成功開啟
        printf("無法開啟檔案 %s 進行寫入\n", filename);
        return;
    }

    for (int i = 0; i < 9; i++) { // 逐列寫入
        for (int j = 0; j < 9; j++) { // 逐行寫入
            if (board[i][j] == 0) {
                fprintf(fp, ".");  // 使用點表示空格
            } else {
                fprintf(fp, "%d", board[i][j]);
            }
        }
        fprintf(fp, "\n");  // 每行結束換行
    }

    fclose(fp); // 關閉檔案
    printf("已成功儲存到 %s\n", filename);
}

int read_from_text_file(int board[][9], const char* filename) {
    FILE *fp = fopen(filename, "r"); // 以讀取模式開啟檔案
    if (fp == NULL) { // 檢查檔案是否成功開啟
        printf("無法開啟檔案 %s 進行讀取\n", filename);
        return 0;
    }

    char line[20];  // 足夠容納一行的緩衝區
    int row = 0;

    // 逐行讀取檔案內容
    while (row < 9 && fgets(line, sizeof(line), fp) != NULL) {
        for (int col = 0; col < 9; col++) {
            if (line[col] == '.') {
                board[row][col] = 0;  // 空格
            } else if (line[col] >= '1' && line[col] <= '9') {
                board[row][col] = line[col] - '0';  // 轉換字元到數字
            } else {
                continue;  // 忽略其他字元（如換行）
            }
        }
        row++;
    }

    fclose(fp); // 關閉檔案

    if (row < 9) { // 檢查是否讀取完整
        printf("警告：檔案格式不正確或檔案不完整\n");
        return 0;
    }

    printf("已成功從 %s 讀取數獨盤面\n", filename);
    return 1;
}

typedef struct {
    int numbers;   // 檔案中的問題總數
    int datasize;  // 每個問題的資料大小（位元組）
} SudokuDataHeader;

typedef struct {
    int id;         // 問題編號
    int data[9][9]; // 盤面資料
} SudokuProblem;

void save_to_binary_file(int board[][9], int problem_id, const char* filename, int is_append) {
    FILE *fp;
    if (is_append) {
        // 檢查檔案是否存在
        fp = fopen(filename, "rb+");
        if (fp == NULL) {
            // 檔案不存在，建立新檔案
            fp = fopen(filename, "wb+");
            if (fp == NULL) {
                printf("無法建立檔案 %s\n", filename);
                return;
            }

            // 寫入新的標頭
            SudokuDataHeader header;
            header.numbers = 1;
            header.datasize = sizeof(SudokuProblem);
            fwrite(&header, sizeof(header), 1, fp);
        } else {
            // 檔案存在，更新標頭中的問題數量
            SudokuDataHeader header;
            fread(&header, sizeof(header), 1, fp);
            header.numbers++;

            // 回到檔案開頭更新標頭
            fseek(fp, 0, SEEK_SET);
            fwrite(&header, sizeof(header), 1, fp);

            // 移動到檔案末尾以添加新問題
            fseek(fp, 0, SEEK_END);
        }
    } else {
        // 建立新檔案
        fp = fopen(filename, "wb");
        if (fp == NULL) {
            printf("無法開啟檔案 %s 進行寫入\n", filename);
            return;
        }

        // 寫入標頭
        SudokuDataHeader header;
        header.numbers = 1;
        header.datasize = sizeof(SudokuProblem);
        fwrite(&header, sizeof(header), 1, fp);
    }

    // 建立並寫入問題
    SudokuProblem problem;
    problem.id = problem_id;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            problem.data[i][j] = board[i][j]; // 將目前盤面的資料複製到問題結構中
        }
    }

    fwrite(&problem, sizeof(problem), 1, fp); // 將問題寫入檔案
    fclose(fp); // 關閉檔案

    printf("已成功儲存到二進位檔案 %s\n", filename);
}

int read_from_binary_file(int board[][9], const char* filename, int problem_index) {
    FILE *fp = fopen(filename, "rb"); // 以二進位讀取模式開啟檔案
    if (fp == NULL) {
        printf("無法開啟檔案 %s 進行讀取\n", filename);
        return 0;
    }

    // 讀取標頭
    SudokuDataHeader header;
    fread(&header, sizeof(header), 1, fp);

    printf("檔案中有 %d 個數獨問題\n", header.numbers);

    if (problem_index < 0 || problem_index >= header.numbers) {
        printf("問題編號 %d 超出範圍 (0-%d)\n", problem_index, header.numbers - 1);
        fclose(fp);
        return 0;
    }

    // 跳到指定的問題位置
    fseek(fp, sizeof(header) + problem_index * header.datasize, SEEK_SET);

    // 讀取問題
    SudokuProblem problem;
    fread(&problem, sizeof(problem), 1, fp);

    // 將問題資料複製到提供的板盤中
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = problem.data[i][j]; // 將讀取到的盤面資料存回傳入的陣列
        }
    }

    printf("已讀取問題 ID: %d\n", problem.id);
    fclose(fp); // 關閉檔案

    return 1; // 回傳成功
}

int factorial(int n) {
    // 終止條件
    if (n <= 1) {
        return 1;
    }
    // 遞迴呼叫
    return n * factorial(n - 1);
}

int solve(int puzzle[][9], int pos) {
    // 終止條件：所有位置都填完了
    if (pos == 81) {
        return 1;  // 成功解出
    }
    
    // 將位置編號轉換為行列座標
    int row = pos / 9;
    int col = pos % 9;
    
    // 如果該位置已有數字，跳到下一個位置
    if (puzzle[row][col] != 0) {
        return solve(puzzle, pos + 1);
    }
    
    // 嘗試填入數字 1-9
    for (int num = 1; num <= 9; num++) {
        // 檢查這個數字是否可以放在這個位置
        if (isValid(num, puzzle, row, col)) {
            // 暫時填入這個數字
            puzzle[row][col] = num;
            
            // 遞迴處理下一個位置
            if (solve(puzzle, pos + 1)) {
                return 1;  // 成功找到解答
            }
            
            // 如果遞迴失敗，回溯：清空該格
            puzzle[row][col] = 0;
        }
    }
    
    // 所有數字都試過，仍無法解出
    return 0;
}

int isValid(int number, int puzzle[][9], int row, int col) {
    int rowStart = (row / 3) * 3;
    int colStart = (col / 3) * 3;
    
    for (int i = 0; i < 9; i++) {
        // 檢查同一行
        if (puzzle[row][i] == number) return 0;
        
        // 檢查同一列
        if (puzzle[i][col] == number) return 0;
        
        // 檢查 3x3 小方格
        if (puzzle[rowStart + (i / 3)][colStart + (i % 3)] == number) return 0;
    }
    
    return 1;
}
int count_empty_cells(int puzzle[][9]) {
    int count = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (puzzle[i][j] == 0) {
                count++;
            }
        }
    }
    return count;
}

int is_valid_solution(int puzzle[][9]) {
    // 檢查每一行
    for (int i = 0; i < 9; i++) {
        int row_check[10] = {0};
        for (int j = 0; j < 9; j++) {
            int num = puzzle[i][j];
            if (num < 1 || num > 9 || row_check[num]) return 0;
            row_check[num] = 1;
        }
    }
    // 檢查每一列
    for (int j = 0; j < 9; j++) {
        int col_check[10] = {0};
        for (int i = 0; i < 9; i++) {
            int num = puzzle[i][j];
            if (num < 1 || num > 9 || col_check[num]) return 0;
            col_check[num] = 1;
        }
    }
    // 檢查每個 3x3 方格
    for (int block_row = 0; block_row < 3; block_row++) {
        for (int block_col = 0; block_col < 3; block_col++) {
            int block_check[10] = {0};
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int num = puzzle[block_row * 3 + i][block_col * 3 + j];
                    if (num < 1 || num > 9 || block_check[num]) return 0;
                    block_check[num] = 1;
                }
            }
        }
    }
    return 1; // 通過所有檢查
}

int main() {
    print_board(board); // 印出原始盤面
    save_to_text_file(board, "sudoku.txt"); // 儲存盤面到檔案
    int new_board[9][9]; // 宣告一個新盤面
    if (read_from_text_file(new_board, "sudoku.txt")) { // 從檔案讀取盤面
        printf("讀取的數獨盤面：\n");
        print_board(new_board); // 印出讀取後的盤面
    } else {
        printf("讀取數獨盤面失敗\n");
    }
    save_to_binary_file(board, 1, "sudoku.bin", 0); // 儲存盤面到二進位檔案
    int binary_board[9][9]; // 宣告一個二進位檔案的盤面
    if (read_from_binary_file(binary_board, "sudoku.bin", 0)) { // 從二進位檔案讀取盤面
        printf("讀取的二進位數獨盤面：\n");
        print_board(binary_board); // 印出讀取後的盤面
    } else {
        printf("讀取二進位數獨盤面失敗\n");
    }
    save_to_binary_file(board, 2, "sudoku.bin", 1); // 追加儲存到二進位檔案
    if (read_from_binary_file(binary_board, "sudoku.bin", 1)) { // 從二進位檔案讀取第二個問題
        printf("讀取的二進位數獨盤面：\n");
        print_board(binary_board); // 印出讀取後的盤面
    } else {
        printf("讀取二進位數獨盤面失敗\n");
    }
   return 0; // 程式結束
}
