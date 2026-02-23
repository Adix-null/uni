#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define BUFFLEN 1024

#define WIDTH 7
#define HEIGHT 6

enum BoardStatus
{
    OK = 0,
    BOARD_FULL = 1,
    INVALID_ROW = -1,
    COLUMN_FULL = -2
};

void render_board(int board[HEIGHT][WIDTH]);

int pick_vacant_column(int board[HEIGHT][WIDTH]);

int check_win(int board[HEIGHT][WIDTH]);

bool check_full(int board[HEIGHT][WIDTH]);

int next_move(int board[HEIGHT][WIDTH], int position, int player);

void deserialize(char *str, int board[HEIGHT][WIDTH]);

char* serialize(int board[HEIGHT][WIDTH]);

void end_game(int board[HEIGHT][WIDTH], int client_socket);

#endif // GAME_LOGIC_H
