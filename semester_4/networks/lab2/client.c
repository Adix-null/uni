#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ftp.h"

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
    server_address.sin_family = AF_INET;   // protocol is IP
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

    printf("This is a simple FTP client\n");

    char input_buffer[BUFFLEN];
    int resp = 0;
    resp = recv_response(s_socket, buffer);
    func_t chosen_func;

    while (resp != LOGIN_OK)
    {
        get_input(input_buffer, "Enter username: ");
        // send_command(s_socket, "AUTH", (char *[]){"TLS", NULL}); no tls
        send_command(s_socket, "USER", (char *[]){input_buffer, NULL});
        resp = recv_response(s_socket, buffer);

        get_input(input_buffer, "Enter password: ");
        send_command(s_socket, "PASS", (char *[]){input_buffer, NULL});
        resp = recv_response(s_socket, buffer);

        if (resp == LOGIN_ERR)
        {
            printf("Invalid credentials\n");
        }        
    }
    
    char path[256];
    client_ctx ctx;
    
    help(0, (char *[]){NULL}, &ctx);
    send_command(s_socket, "CDUP", (char*[]){NULL});
    ctx.resp_code = recv_response(s_socket, buffer);

    ctx.s_socket = s_socket;
    ctx.resp_code = resp;
    while (ctx.resp_code != SESH_CLOSED)
    {
        send_command(s_socket, "PWD", (char *[]){NULL});
        resp = recv_response(s_socket, buffer);
        extract_pwd(buffer, path, sizeof(path));
        printf("%s> ", path);

        get_input(input_buffer, "");
        switch_func(input_buffer, &ctx);
    }

    closesocket(s_socket);
    WSACleanup();
    return 0;
}