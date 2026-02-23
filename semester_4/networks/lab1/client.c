#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "game_logic.h"

int main(int argc, char *argv[])
{
    WSADATA wsadata;
    unsigned int port;
    int s_socket;
    struct sockaddr_in server_address;

    char buffer[BUFFLEN];

    if (argc != 3)
    {
        fprintf(stderr, "USAGE: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[2]);

    if ((port < 1) || (port > 65535))
    {
        printf("ERROR #1: invalid port specified.\n");
        exit(1);
    }

    WSAStartup(MAKEWORD(2, 2), &wsadata);

    /* Creation of client socket */
    if ((s_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "ERROR #2: cannot create socket.\n");
        exit(1);
    }

    /* Clean server adress memory */
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET; // protocol is IP
    server_address.sin_port = htons(port); // port set

    /* Parse and set IP */
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    printf("Connecting to %s:%d ...\n", inet_ntoa(server_address.sin_addr), port);

    /* Connect to server */
    if (connect(s_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        fprintf(stderr, "ERROR #4: error in connect().\n");
        exit(1);
    }
    printf("Connected to server %s:%d\n", inet_ntoa(server_address.sin_addr), port);

    int board[HEIGHT][WIDTH];
    memset(board, '0', sizeof(board));

    while(true)
    {        
        
        /* Send message to server */
        memset(&buffer, 0, BUFFLEN);
        fgets(buffer, BUFFLEN, stdin);
        send(s_socket, buffer, strlen(buffer), 0);
        
        /* Receive message from server */
        memset(&buffer, 0, BUFFLEN);
        recv(s_socket, buffer, BUFFLEN, 0);
        
        // if (buffer[0] == HEADER_MESSAGE)
        // {
        //     printf("Server says: %.*s\n", n - 1, buffer + 1);
        // }
        if(buffer[0] == HEADER_BOARD)
        {
            deserialize(buffer, board);
            render_board(board);
        }

        if (strlen(buffer) <= 0)
        {
            printf("Server closed the connection\n");
            break;
        }
    }
    closesocket(s_socket);

    WSACleanup();
    return 0;
}