#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define BUFFLEN 1024

#define WIDTH 7
#define HEIGHT 6

enum BoardStatus
{
    OK = 0,
    GAME_OVER = 1,
    INVALID_COLUMN = -1,
    COLUMN_FULL = -2
};

void render_board(int board[HEIGHT][WIDTH]);

int pick_vacant_column(int board[HEIGHT][WIDTH]);

int check_win(int board[HEIGHT][WIDTH]);

bool check_full(int board[HEIGHT][WIDTH]);

int next_move(int board[HEIGHT][WIDTH], int position, int player);

char *serialize(int board[HEIGHT][WIDTH], enum BoardStatus game_status, int winner);

void deserialize(char *str, int board[HEIGHT][WIDTH], enum BoardStatus *game_status, int *winner);

void end_game(int board[HEIGHT][WIDTH], int client_socket);

#endif // GAME_LOGIC_H
