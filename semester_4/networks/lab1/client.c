#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFLEN 1024

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

    printf("Enter the message: ");
    fgets(buffer, BUFFLEN, stdin);
    /* Send message to server */
    send(s_socket, buffer, strlen(buffer), 0);
    memset(&buffer, 0, BUFFLEN);

    /* Receive message from server */
    recv(s_socket, buffer, BUFFLEN, 0);
    printf("Server sent: %s\n", buffer);

    closesocket(s_socket);
    WSACleanup();
    return 0;
}