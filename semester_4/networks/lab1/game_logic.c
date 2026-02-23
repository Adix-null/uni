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
            if (board[i][j] == '0')
            {
                printf(". ");
            }
            else if (board[i][j] == '1')
            {
                printf("X ");
            }
            else if (board[i][j] == '2')
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

int check_win(int board[HEIGHT][WIDTH])
{
    for (int player = 1; player < 3; player++)
    {
        // Check horizontal
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

        // Check vertical
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

        // Check diagonal (top-left to bottom-right)
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

        // Check diagonal (top-right to bottom-left)
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

enum BoardStatus next_move(int board[HEIGHT][WIDTH], int position, int player)
{
    if (position < 0 || position >= WIDTH)
    {
        return INVALID_ROW;
    }

    if (check_full(board))
    {
        return BOARD_FULL;
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

char *serialize(int board[HEIGHT][WIDTH])
{
    static char buffer[BUFFLEN];
    buffer[0] = HEADER_BOARD;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            buffer[1 + (i * WIDTH + j)] = board[i][j] + '0';
        }
    }
    return buffer;
}

void deserialize(char *str, int board[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            board[i][j] = str[1 + (i * WIDTH + j)];
        }
    }
}

void end_game(int board[HEIGHT][WIDTH], int client_socket, char *messageBuffer)
void deserialize(char *str, int board[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            board[i][j] = str[1 + (i * WIDTH + j)];
        }
    }
}

void end_game(int board[HEIGHT][WIDTH], int client_socket, char *messageBuffer)
{
    int winner = check_win(board);
    if (winner == 0)
    {
        char tieMessage[BUFFLEN];
        sprintf(tieMessage, "Tie");
        printf("%s\n", tieMessage);
        put_message_in_queue(tieMessage, messageBuffer);
    }
    else
    {
        char winMessage[BUFFLEN];
        sprintf(winMessage, "Player %d wins", winner);
        printf("%s\n", winMessage);
        put_message_in_queue(winMessage, messageBuffer);
        put_message_in_queue(winMessage, messageBuffer);
    }
    closesocket(client_socket);
}

void put_message_in_queue(char *message, char *messageBuffer)
{
    strncpy(messageBuffer + strlen(messageBuffer), message, strlen(message));
    messageBuffer[strlen(messageBuffer)] = '\n';
    messageBuffer[strlen(messageBuffer) + 1] = '\0';
    printf("Message added to queue: %s\n", message);
}

void print_messages_in_queue(char *messageBuffer)
{
    char *token = strtok(messageBuffer, "\n");
    while (token != NULL)
    {
        printf("Server says: %s\n", token);
        token = strtok(NULL, "\n");
    }
}

int send_info(int client_socket, int board[HEIGHT][WIDTH], char *messageBuffer)
{
    char *boardMessage = serialize(board);
    int board_len = strlen(boardMessage);
    int message_len = strlen(messageBuffer);

    char combined[BUFFLEN];
    memcpy(combined, boardMessage, board_len);
    combined[board_len + 1] = HEADER_MESSAGE;
    memcpy(combined + board_len + 1, messageBuffer, message_len);

    for (int i = 0; i < strlen(combined); i++)
    {
        printf("%d ", combined[i]);
    }

    return send(client_socket, combined, board_len + 1 + message_len, 0);
}

void parse_info(char *buffer, int board[HEIGHT][WIDTH], char *messageBuffer)
{
    if (buffer[0] == HEADER_BOARD)
    {
        deserialize(buffer, board);
    }
    if (buffer[HEIGHT * WIDTH + 1] == HEADER_MESSAGE)
    {
        strncpy(messageBuffer, buffer + HEIGHT * WIDTH + 2, strlen(buffer) - HEIGHT * WIDTH - 2);
    }
}
