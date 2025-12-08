#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdbool.h>

#define BOARD_SIZE 9

void board_init(char *board);
void board_print(const char *board);
bool board_place(char *board, int pos, char player);
bool board_check_win(const char *board, char player);
bool board_is_full(const char *board);

static inline bool cell_is_empty(const char *cell) { return *cell == ' '; }

#endif
