#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "game_logic.h"

int main(int argc, char *argv[])
{
    WSADATA wsadata;
    unsigned int port;
    int listening_socket;
    int client_socket;

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    socklen_t client_addresslen;

    int s_len;
    int r_len;
    char buffer[BUFFLEN];

    if (argc != 2)
    {
        printf("USAGE: %s <port>\n", argv[0]);
        exit(1);
    }
    
    port = atoi(argv[1]);
    
    if ((port < 1) || (port > 65535))
    {
        printf("ERROR #1: invalid port specified.\n");
        exit(1);
    }

    WSAStartup(MAKEWORD(2, 2), &wsadata);

    /* Creation of server socket */
    if ((listening_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "ERROR #2: cannot create listening socket.\n");
        exit(1);
    }

    /* Clean server adress memory */
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET; // protocol is IP

    /* All system ip adresses will be accepted */
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port); // port set

    /* Bind server adress to socket */
    if (bind(listening_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        fprintf(stderr, "ERROR #3: bind listening socket.\n");
        exit(1);
    }

    struct sockaddr_in bound_address;
    int address_len = sizeof(bound_address);
    getsockname(listening_socket, (struct sockaddr *)&bound_address, &address_len);

    printf("Server is running on %s:%d\n", inet_ntoa(bound_address.sin_addr), ntohs(bound_address.sin_port));

    /* listening_socket will await new clients, max 5 in queue */
    if (listen(listening_socket, 5) < 0)
    {
        fprintf(stderr, "ERROR #4: error in listen().\n");
        exit(1);
    }

    srand(time(NULL));
    while (true)
    {
        /* Clean client adress memory */
        memset(&client_address, 0, sizeof(client_address));
        
        /* Await new client connections */
        client_addresslen = sizeof(struct sockaddr);
        printf("Awaiting new client connections...\n");
        if ((client_socket = accept(listening_socket, (struct sockaddr *)&client_address, &client_addresslen)) < 0)
        {
            fprintf(stderr, "ERROR #5: error occured accepting connection.\n");
            exit(1);
        }
        printf("Client connected from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        int board[HEIGHT][WIDTH];
        memset(board, 0, sizeof(board));

        while (true)
        {
            if (check_full(board) || check_win(board) != 0)
            {
                end_game(board, client_socket);
                break;
            }

            bool error = false;
            do
            {
                //send_message(client_socket, "Your turn\n");
                error = false;
                errno = 0;
                memset(&buffer, 0, sizeof(buffer));

                int rowChoice;                
                s_len = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
                sscanf(buffer, "%d", &rowChoice);

                if (s_len <= 0)
                {
                    closesocket(client_socket);
                    break;
                }
    
                if (errno != 0 || rowChoice < 0 || rowChoice > WIDTH - 1)
                {
                    //send_message(client_socket, "Invalid row received\n");
                    error = true;
                    continue;
                }

                int status = next_move(board, rowChoice, 1);
                printf("Status: %d\n", status);
                if(status == COLUMN_FULL)
                {
                    //send_message(client_socket, "Column is full, choose another one\n");
                    error = true;
                    continue;
                }

            } while (error);

            srand(time(NULL));
            int move = pick_vacant_column(board);
            
            if(move != -1)
            {
                next_move(board, move, 2);
                char* message = serialize(board);
                
                /* Send the combined info to client*/
                r_len = send(client_socket, message, strlen(message), 0);
                printf("IP: %s Sent: %d Received: %d\n", inet_ntoa(client_address.sin_addr), strlen(message), r_len);
            }
            else
            {
                end_game(board, client_socket);
                break;
            }
        }
    }
    closesocket(client_socket);

    WSACleanup();
    return 0;
}
