#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "ftp.h"

dict_entry func_dictionary[] = {
    {"help", help},
    {"quit", quit},
    {"ls", ls},
    {"cd", cd},
    {"mkdir", mkdir},
    {"rm", rm},
    {"rmdir", rmdir},
    {"get", getfile},
    {"put", putfile},
    {NULL, NULL}
};

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

void get_input(char *inp_buffer, char *msg)
{
    printf("%s", msg);
    memset(inp_buffer, 0, BUFFLEN);
    fgets(inp_buffer, BUFFLEN, stdin);
    inp_buffer[strcspn(inp_buffer, "\r\n")] = 0;
}

void send_command(int s_socket, char *command, char *args[])
{
    static char buffer[BUFFLEN];
    memset(&buffer, 0, BUFFLEN);

    strcat(buffer, command);

    for (int i = 0; args[i] != NULL; i++)
    {
        strcat(buffer, " ");
        strcat(buffer, args[i]);
    }
    strcat(buffer, "\r\n");
    send(s_socket, buffer, strlen(buffer), 0);
}

int recv_response(int s_socket, char buffer[BUFFLEN])
{
    memset(buffer, 0, BUFFLEN);
    recv(s_socket, buffer, BUFFLEN, 0);
    if(PRINT_MODE == 1)
    {
        printf("Response: %s", buffer);
    }

    int resp = atoi(buffer);
    return resp;
}

void extract_pwd(char *resp, char *out, size_t out_len)
{
    const char *start = strchr(resp, '"');
    if (!start)
    {
        out[0] = '\0';
        return;
    }

    start++;
    const char *end = strchr(start, '"');
    if (!end)
    {
        out[0] = '\0';
        return;
    }

    size_t len = end - start;
    if (len >= out_len)
        len = out_len - 1;

    strncpy(out, start, len);
    out[len] = '\0';
}

void switch_func(char *inp, void *ctx)
{
    char buffer[1024];
    strncpy(buffer, inp, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    // get the command name
    char *cmd = strtok(buffer, " \t\r\n");
    if (!cmd)
        return; // empty input

    // get arguments
    char *argv[MAX_ARGS];
    int argc = 0;
    char *token;
    while ((token = strtok(NULL, " \t\r\n")) && argc < MAX_ARGS)
    {
        argv[argc++] = token;
    }

    // Lookup associated function
    for (int i = 0; func_dictionary[i].key != NULL; i++)
    {
        if (strcmp(func_dictionary[i].key, cmd) == 0)
        {
            func_dictionary[i].value(argc, argv, ctx);
            return;
        }
    }

    printf("Unknown command: %s\n", cmd);
}

void open_data_connection(client_ctx *ctx, char *buffer, int *data_socket_num)
{
    send_command(ctx->s_socket, "PASV", (char *[]){NULL});
    ctx->resp_code = recv_response(ctx->s_socket, buffer);
    if (ctx->resp_code != PASV_OK)
    {
        printf("Failed to enter passive mode.\n");
        return;
    }

    // Parse PASV resp to get ip/port
    int h1, h2, h3, h4, p1, p2;
    sscanf(buffer, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)", &h1, &h2, &h3, &h4, &p1, &p2);
    char data_ip[16];
    sprintf(data_ip, "%d.%d.%d.%d", h1, h2, h3, h4);
    int data_port = p1 * 256 + p2;

    // Establish data connection
    int data_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in data_addr;
    memset(&data_addr, 0, sizeof(data_addr));
    data_addr.sin_family = AF_INET;
    data_addr.sin_port = htons(data_port);
    inet_pton(AF_INET, data_ip, &data_addr.sin_addr);
    
    if (connect(data_socket, (struct sockaddr *)&data_addr, sizeof(data_addr)) < 0)
    {
        printf("Failed to connect to data socket.\n");
        closesocket(data_socket);
        *data_socket_num = -1;
        return;
    }
    if(PRINT_MODE == 1)
    {
        printf("Data connection established to %s:%d\n", data_ip, data_port);
    }
    *data_socket_num = data_socket;
}
void close_data_connection(int data_socket)
{
    closesocket(data_socket);
}

void parse_list(char *list, char **files, int *file_count, char **folders, int *folder_count)
{
    *file_count = 0;
    *folder_count = 0;

    char *line = strtok(list, "\r\n");
    while (line != NULL)
    {
        // Skip empty lines
        if (strlen(line) == 0)
        {
            line = strtok(NULL, "\r\n");
            continue;
        }

        // d == folder, - = file
        int is_dir = (line[0] == 'd');

        char *name = NULL;
        char *token = strtok(NULL, " \t");
        char line_copy[1024];
        strncpy(line_copy, line, sizeof(line_copy) - 1);
        line_copy[sizeof(line_copy) - 1] = '\0';
        
        // file/folder name is 9th token
        char *fields[9];
        int field_count = 0;
        char *tok = strtok(line_copy, " \t");
        while (tok != NULL && field_count < 9)
        {
            fields[field_count++] = tok;
            tok = strtok(NULL, " \t");
        }

        if (field_count < 9)
        {
            line = strtok(NULL, "\r\n");
            continue;
        }

        name = fields[8];

        if (is_dir)
            folders[(*folder_count)++] = strdup(name);
        else
            files[(*file_count)++] = strdup(name);

        line = strtok(NULL, "\r\n");
    }
}

int delete_action(client_ctx *ctx, const char *path, int is_dir)
{
    char buffer[BUFFLEN];
    if (is_dir)
    {
        send_command(ctx->s_socket, "RMD", (char *[]){(char *)path, NULL});
    }
    else
    {
        send_command(ctx->s_socket, "DELE", (char *[]){(char *)path, NULL});
    }
    ctx->resp_code = recv_response(ctx->s_socket, buffer);
    if (ctx->resp_code != CD_OK)
    {
        printf("Failed to delete %s\n", path);
        return -1;
    }
    return 0;
}

void help   (int argc, char *argv[], void *ctx)
{
    printf("%s", menu);
}

void ls     (int argc, char *argv[], void *ctx)
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

void cd     (int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    if (argc < 1)
    {
        printf("Usage: cd <path>\n");
        return;
    }

    send_command(context->s_socket, "CWD", (char *[]){argv[0], NULL});

    char buffer[BUFFLEN];
    context->resp_code = recv_response(context->s_socket, buffer);
    if(context->resp_code == CD_ERR)
    {
        printf("%s", buffer);
    }
}

void mkdir  (int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    if (argc < 1)
    {
        printf("Usage: mkdir <dirname> \n");
        return;
    }

    send_command(context->s_socket, "MKD", (char *[]){argv[0], NULL});
    char buffer[BUFFLEN];
    context->resp_code = recv_response(context->s_socket, buffer);
    if (context->resp_code == CD_ERR)
    {
        printf("%s", buffer);
    }
}

void rm     (int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    if (argc < 1)
    {
        printf("Usage: rm <filename>\n");
        return;
    }

    send_command(context->s_socket, "DELE", (char *[]){argv[0], NULL});
    char buffer[BUFFLEN];
    context->resp_code = recv_response(context->s_socket, buffer);
    if (context->resp_code == CD_ERR)
    {
        printf("%s", buffer);
    }
}

void rmdir  (int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    if (argc < 1)
    {
        printf("Usage: rmdir <dirname> \n");
        return;
    }
    
    send_command(context->s_socket, "RMD", (char *[]){argv[0], NULL});
    char buffer[BUFFLEN];
    context->resp_code = recv_response(context->s_socket, buffer);
    if (context->resp_code == CD_ERR)
    {
        printf("%s", buffer);
    }
}

void getfile(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    if (argc < 1)
    {
        printf("Usage: get <path>\n");
        return;
    }

    char buffer[16384];
    char *path = argv[0];
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

    FILE *f = fopen(argv[0], "wb");
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

void putfile(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    if (argc < 1)
    {
        printf("Usage: put <path>\n");
        return;
    }

    char buffer[16384];
    char *path = argv[0];
    int data_socket;

    open_data_connection(context, buffer, &data_socket);

    send_command(context->s_socket, "STOR", (char *[]){path, NULL});

    context->resp_code = recv_response(context->s_socket, buffer);
    if (context->resp_code != FILE_OK)
    {
        printf("Server rejected RETR: %s", buffer);
        close_data_connection(data_socket);
        return;
    }

    FILE *f = fopen(argv[0], "rb");
    if (f == NULL)
    {
        printf("File cannot be opened");
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
        printf("Possible transfer error: %s", buffer);
    }
}

void quit(int argc, char *argv[], void *ctx)
{
    client_ctx *context = (client_ctx *)ctx;
    send_command(context->s_socket, "QUIT", (char *[]){NULL});
    
    char buffer[BUFFLEN];
    context->resp_code = recv_response(context->s_socket, buffer);
}
