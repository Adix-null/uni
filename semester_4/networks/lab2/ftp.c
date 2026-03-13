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

dict_entry func_dictionary[] = {
    {"help", help},
    {"quit", quit},
    {"ls", ls},
    {"cd", cd},
    {"mkdir", mkdir},
    {"rm", rm},
    {"rmdir", rmdir},
    {"get", getfile},
    {"getdir", getdir},
    {"put", putfile},
    {"putdir", putdir},
    {NULL, NULL}};

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

int recurse_remote(client_ctx *ctx, const char *path, tree_action_fn action)
{
    char buffer[BUFFLEN];
    char list_buf[FILE_MAX_CHUNK];
    int list_len = 0;

    // go to target folder
    send_command(ctx->s_socket, "CWD", (char *[]){(char *)path, NULL});
    ctx->resp_code = recv_response(ctx->s_socket, buffer);
    if (ctx->resp_code != CD_OK)
    {
        printf("Failed to CWD into %s\n", path);
        return -1;
    }

    // list the contents
    int data_socket;
    open_data_connection(ctx, buffer, &data_socket);
    if (data_socket < 0)
        return -1;

    send_command(ctx->s_socket, "LIST", (char *[]){NULL});
    recv_response(ctx->s_socket, buffer);

    int n;
    while ((n = recv(data_socket, list_buf + list_len, sizeof(list_buf) - list_len - 1, 0)) > 0)
        list_len += n;
    list_buf[list_len] = '\0';

    close_data_connection(data_socket);
    recv_response(ctx->s_socket, buffer); 

    // Parse the print result into char*
    char *files[256], *folders[256];
    int file_count, folder_count;
    parse_list(list_buf, files, &file_count, folders, &folder_count);

    // do the action on the files
    for (int i = 0; i < file_count; i++)
    {
        action(ctx, files[i], 0);
        free(files[i]);
    }

    // recurse to subfolders
    for (int i = 0; i < folder_count; i++)
    {
        action(ctx, folders[i], 1);

        // extend local_path before recursing
        char saved_local_path[1024];
        strncpy(saved_local_path, ctx->local_path, sizeof(saved_local_path));
        snprintf(ctx->local_path, sizeof(ctx->local_path), "%s\\%s", ctx->local_path, folders[i]);

        recurse_remote(ctx, folders[i], action);

        // restore local_path
        strncpy(ctx->local_path, saved_local_path, sizeof(ctx->local_path));
        send_command(ctx->s_socket, "CDUP", (char *[]){NULL});
        ctx->resp_code = recv_response(ctx->s_socket, buffer);

        free(folders[i]);
    }

    return 0;
}

int upload_recurse(client_ctx *ctx, const char *local_path, const char *remote_path)
{
    char buffer[BUFFLEN];

    char search_path[BUFFLEN];
    snprintf(search_path, sizeof(search_path), "%s\\*", local_path);
    
    WIN32_FIND_DATAA find_data;
    HANDLE hFind = FindFirstFileA(search_path, &find_data);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("Failed to open local directory %s\n", local_path);
        return -1;
    }

    // Create remote folder
    send_command(ctx->s_socket, "MKD", (char *[]){(char *)remote_path, NULL});
    recv_response(ctx->s_socket, buffer);

    send_command(ctx->s_socket, "CWD", (char *[]){(char *)remote_path, NULL});
    ctx->resp_code = recv_response(ctx->s_socket, buffer);

    if (ctx->resp_code != CD_OK)
    {
        printf("Failed to CWD into %s\n", remote_path);
        return -1;
    }

    do
    {
        // skip . and ..
        if (strcmp(find_data.cFileName, ".") == 0 || strcmp(find_data.cFileName, "..") == 0)
        {
            continue;
        }

        char child_local[2048];
        snprintf(child_local, sizeof(child_local), "%s\\%s", local_path, find_data.cFileName);

        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            upload_recurse(ctx, child_local, find_data.cFileName);
            // CWD back to parent folder
            send_command(ctx->s_socket, "CDUP", (char *[]){NULL});
            recv_response(ctx->s_socket, buffer);
        }
        else
        {
            char *put_argv[] = {child_local, find_data.cFileName, NULL};
            putfile(2, put_argv, ctx);
        }
    } while (FindNextFileA(hFind, &find_data));

    FindClose(hFind);
    return 0;
}

void parse_list(char *list, char **files, int *file_count, char **folders, int *folder_count)
{
    *file_count = 0;
    *folder_count = 0;

    char *line_saveptr;
    char *line = strtok_r(list, "\r\n", &line_saveptr);
    while (line != NULL)
    {
        if (strlen(line) == 0)
        {
            line = strtok_r(NULL, "\r\n", &line_saveptr);
            continue;
        }

        // d = folder, - = file
        bool is_dir = (line[0] == 'd');

        char line_copy[1024];
        strncpy(line_copy, line, sizeof(line_copy) - 1);
        line_copy[sizeof(line_copy) - 1] = '\0';

        // file/folder name is 9th token
        char *fields[9];
        int field_count = 0;
        char *field_saveptr;
        char *tok = strtok_r(line_copy, " \t", &field_saveptr);
        while (tok != NULL && field_count < 9)
        {
            fields[field_count++] = tok;
            tok = strtok_r(NULL, " \t", &field_saveptr);
        }

        if (field_count < 9)
        {
            line = strtok_r(NULL, "\r\n", &line_saveptr);
            continue;
        }

        char *name = fields[8];
        if (is_dir)
            folders[(*folder_count)++] = strdup(name);
        else
            files[(*file_count)++] = strdup(name);

        line = strtok_r(NULL, "\r\n", &line_saveptr);
    }
}

int delete_action(client_ctx *ctx, const char *path, bool is_dir)
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

int download_action(client_ctx *ctx, const char *path, bool is_dir)
{
    char full_local_path[BUFFLEN];
    snprintf(full_local_path, sizeof(full_local_path), "%s\\%s", ctx->local_path, path);

    if (is_dir)
    {
        CreateDirectoryA(full_local_path, NULL);
        return 0;
    }

    char buffer[BUFFLEN];
    int data_socket;
    open_data_connection(ctx, buffer, &data_socket);
    if (data_socket < 0)
        return -1;

    send_command(ctx->s_socket, "RETR", (char *[]){(char *)path, NULL});
    ctx->resp_code = recv_response(ctx->s_socket, buffer);
    if (ctx->resp_code != FILE_OK)
    {
        printf("Failed to RETR %s\n", path);
        close_data_connection(data_socket);
        return -1;
    }

    FILE *f = fopen(full_local_path, "wb");
    if (f == NULL)
    {
        printf("Failed to open local file %s\n", full_local_path);
        close_data_connection(data_socket);
        return -1;
    }

    int n;
    char file_buf[FILE_MAX_CHUNK];
    while ((n = recv(data_socket, file_buf, sizeof(file_buf), 0)) > 0)
        fwrite(file_buf, 1, n, f);

    fclose(f);
    close_data_connection(data_socket);
    recv_response(ctx->s_socket, buffer);
    return 0;
}
