#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include "command_list.h"
#include "ftp.h"

const char *menu =
    "Menu:\n\
help - show this menu\n\
ls - view current folder contents\n\
cd <path> - go to path\n\
mkdir <dirname> - create empty directory\n\
rm <filename> - delete file\n\
rmdir <dirname> - delete empty directory\n\
get <filename> - download file\n\
put <filename> - upload file\n\
getdir <dirname> - download directory\n\
putdir <dirname> - upload directory\n\
quit - close session\n\
";

void help(int argc, char *argv[], void *ctx)
{
    printf("%s", menu);
}

void ls(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;

    int data_socket;
    char buffer[BUFFLEN] = {0};
    open_data_connection(context, buffer, &data_socket);

    send_command(context->s_socket, "LIST", (char *[]){NULL});

    int n;
    while ((n = recv(data_socket, buffer, sizeof(buffer), 0)) > 0)
    {
        buffer[n] = '\0';
        printf("%s", buffer);
    }

    close_data_connection(data_socket);
    recv_response(context->s_socket, buffer);
}

void cd(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    char *path = argv[0];

    if (argc < 1)
    {
        printf("Usage: cd <path>\n");
        return;
    }

    send_command(context->s_socket, "CWD", (char *[]){path, NULL});

    char buffer[BUFFLEN];
    context->resp_code = recv_response(context->s_socket, buffer);
    if (context->resp_code == CD_ERR)
    {
        printf("%s", buffer);
    }
}

void mkdir(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    char *path = argv[0];

    if (argc < 1)
    {
        printf("Usage: mkdir <dirname> \n");
        return;
    }

    send_command(context->s_socket, "MKD", (char *[]){path, NULL});
    char buffer[BUFFLEN];
    context->resp_code = recv_response(context->s_socket, buffer);
    if (context->resp_code == CD_ERR)
    {
        printf("%s", buffer);
    }
}

void rm(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    char *path = argv[0];

    if (argc < 1)
    {
        printf("Usage: rm <filename>\n");
        return;
    }

    send_command(context->s_socket, "DELE", (char *[]){path, NULL});
    char buffer[BUFFLEN];
    context->resp_code = recv_response(context->s_socket, buffer);
    if (context->resp_code == CD_ERR)
    {
        printf("%s", buffer);
    }
}

void rmdir(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    char *path = argv[0];

    if (argc < 1)
    {
        printf("Usage: rmdir <dirname> \n");
        return;
    }

    char buffer[BUFFLEN];

    recurse_remote(context, path, delete_action);

    // delete the empty folder at the end
    send_command(context->s_socket, "CDUP", (char *[]){NULL});
    recv_response(context->s_socket, buffer);

    delete_action(context, path, 1);
}

void getfile(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    char *path = argv[0];
    if (argc < 1)
    {
        printf("Usage: get <path>\n");
        return;
    }

    char buffer[FILE_MAX_CHUNK];
    int data_socket;

    open_data_connection(context, buffer, &data_socket);

    send_command(context->s_socket, "RETR", (char *[]){path, NULL});

    context->resp_code = recv_response(context->s_socket, buffer);
    if (context->resp_code != FILE_OK)
    {
        printf("Server rejected RETR: %s", buffer);
        close_data_connection(data_socket);
        return;
    }

    FILE *f = fopen(path, "wb");
    if (f == NULL)
    {
        printf("File cannot be opened");
        return;
    }

    int n;
    while ((n = recv(data_socket, buffer, sizeof(buffer), 0)) > 0)
    {
        fwrite(buffer, 1, n, f);
    }
    fclose(f);
    close_data_connection(data_socket);

    context->resp_code = recv_response(context->s_socket, buffer);
    if (context->resp_code != FILE_TRANSFER_OK)
    {
        printf("Possible transfer error: %s", buffer);
    }
}

void getdir(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    char *path = argv[0];

    if (argc < 1)
    {
        printf("Usage: getdir <dirname> \n");
        return;
    }

    char buffer[BUFFLEN];

    strncpy(context->local_path, path, sizeof(context->local_path) - 1);

    !CreateDirectoryA(context->local_path, NULL);
    recurse_remote(context, path, download_action);

    // nullify local path
    context->local_path[0] = '\0';

    send_command(context->s_socket, "CDUP", (char *[]){NULL});
    recv_response(context->s_socket, buffer);
}

void putfile(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    char *path = argv[0];
    if (argc < 1)
    {
        printf("Usage: put <path>\n");
        return;
    }

    char buffer[BUFFLEN];
    char *remote_name = argc >= 2 ? argv[1] : argv[0];

    FILE *f = fopen(path, "rb");
    if (f == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    int data_socket;
    open_data_connection(context, buffer, &data_socket);
    if (data_socket < 0)
    {
        printf("Failed to open data connection.\n");
        fclose(f);
        return;
    }

    send_command(context->s_socket, "STOR", (char *[]){remote_name, NULL});
    context->resp_code = recv_response(context->s_socket, buffer);
    if (context->resp_code != FILE_OK)
    {
        printf("Server rejected STOR: %s", buffer);
        close_data_connection(data_socket);
        fclose(f);
        return;
    }

    int n;
    while ((n = fread(buffer, 1, sizeof(buffer), f)) > 0)
    {
        if (send(data_socket, buffer, n, 0) < 0)
        {
            printf("Failed to send data.\n");
            break;
        }
    }
    fclose(f);
    close_data_connection(data_socket);

    context->resp_code = recv_response(context->s_socket, buffer);
    if (context->resp_code != FILE_TRANSFER_OK)
    {
        printf("Transfer error: %s", buffer);
    }
}

void putdir(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    char *path = argv[0];

    if (argc < 1)
    {
        printf("Usage: putdir <path>\n");
        return;
    }

    char buffer[BUFFLEN];

    //set the remote path to upload into
    memset(context->remote_path, 0, sizeof(context->remote_path));
    strncpy(context->remote_path, path, sizeof(context->remote_path) - 1);

    upload_recurse(context, path, path);

    send_command(context->s_socket, "CDUP", (char *[]){NULL});
    recv_response(context->s_socket, buffer);
}

void quit(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    send_command(context->s_socket, "QUIT", (char *[]){NULL});

    char buffer[BUFFLEN];
    context->resp_code = recv_response(context->s_socket, buffer);
}
