#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "game_logic.h"

void render_board(int board[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (board[i][j] == 0)
            {
                printf(". ");
            }
            else if (board[i][j] == 1)
            {
                printf("X ");
            }
            else if (board[i][j] == 2)
            {
                printf("O ");
            }
            else
            {
                printf("%d ", board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int check_win(int board[HEIGHT][WIDTH])
{
    for (int player = 1; player < 3; player++)
    {
        // Check - horizontal
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH - 3; j++)
            {
                if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player)
                {
                    return player;
                }
            }
        }
        
        // Check | vertical
        for (int i = 0; i < HEIGHT - 3; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player)
                {
                    return player;
                }
            }
        }
        
        // Check \ diagonal
        for (int i = 0; i < HEIGHT - 3; i++)
        {
            for (int j = 0; j < WIDTH - 3; j++)
            {
                if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player && board[i + 3][j + 3] == player)
                {
                    return player;
                }
            }
        }
        
        // Check / diagonal
        for (int i = 0; i < HEIGHT - 3; i++)
        {
            for (int j = 3; j < WIDTH; j++)
            {
                if (board[i][j] == player && board[i + 1][j - 1] == player && board[i + 2][j - 2] == player && board[i + 3][j - 3] == player)
                {
                    return player;
                }
            }
        }
    }
    return 0;
}

bool check_full(int board[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

int pick_vacant_column(int board[HEIGHT][WIDTH])
{
    int vacant_columns[WIDTH];
    int count = 0;
    for (int j = 0; j < WIDTH; j++)
    {
        if (board[0][j] == 0)
        {
            vacant_columns[count] = j;
            count++;
        }
    }
    if (count == 0)
    {
        return -1;
    }
    return vacant_columns[rand() % count];
}

int next_move(int board[HEIGHT][WIDTH], int position, int player)
{
    if (position < 0 || position >= WIDTH)
    {
        return INVALID_COLUMN;
    }

    if (check_full(board))
    {
        return GAME_OVER;
    }

    for (int i = HEIGHT - 1; i >= 0; i--)
    {
        if (board[i][position] == 0)
        {
            board[i][position] = player;
            return OK;
        }
    }
    return COLUMN_FULL;
}

char *serialize(int board[HEIGHT][WIDTH], enum BoardStatus game_status, int winner)
{
    static char buffer[BUFFLEN];
    buffer[0] = game_status + '0';
    buffer[1] = winner + '0';
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            buffer[2 + (i * WIDTH + j)] = board[i][j] + '0';
        }
    }
    return buffer;
}

void deserialize(char *str, int board[HEIGHT][WIDTH], enum BoardStatus *game_status, int *winner)
{
    *game_status = str[0] - '0';
    *winner = str[1] - '0';
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            board[i][j] = str[2 + (i * WIDTH + j)] - '0';
        }
    }
}

void end_game(int board[HEIGHT][WIDTH], int client_socket)
{
    int winner = check_win(board);
    printf("Game over! Winner: %d\n", winner);
    char *message = serialize(board, GAME_OVER, winner);
    send(client_socket, message, strlen(message), 0);    
    closesocket(client_socket);
}
