#include "tictactoe.h"
#include <stdio.h>

static int read_move(void) {
    int pos;
    printf("Enter position (1-9): ");
    if (scanf("%d", &pos) != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        return -1;
    }
    return pos;
}

int main(void) {
    char board[BOARD_SIZE];
    board_init(board);

    char player = 'X';
    while (1) {
        board_print(board);
        printf("Player %c's turn.\n", player);

        int pos = read_move();
        if (!board_place(board, pos, player)) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        if (board_check_win(board, player)) {
            board_print(board);
            printf("Player %c wins!\n", player);
            break;
        }

        if (board_is_full(board)) {
            board_print(board);
            printf("It's a draw!\n");
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }

    return 0;
}
