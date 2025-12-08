#include "tictactoe.h"
#include <stdio.h>

void board_init(char *board) {
    for (int i = 0; i < BOARD_SIZE; i++) board[i] = ' ';
}

void board_print(const char *board) {
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf(" %c ", board[i]);
        if (i % 3 != 2) printf("|");
        if (i % 3 == 2 && i != 8) printf("\n---+---+---\n");
    }
    printf("\n\n");
}

bool board_place(char *board, int pos, char player) {
    if (pos < 1 || pos > 9) return false;
    char *cell = &board[pos - 1];     
    if (!cell_is_empty(cell)) return false;
    *cell = player;
    return true;
}

bool board_check_win(const char *b, char p) {
    const int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (int i = 0; i < 8; i++) {
        if (b[wins[i][0]] == p && b[wins[i][1]] == p && b[wins[i][2]] == p) return true;
    }
    return false;
}

bool board_is_full(const char *board) {
    for (int i = 0; i < BOARD_SIZE; i++) if (board[i] == ' ') return false;
    return true;
}
