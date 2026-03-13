#ifndef FTP_H
#define FTP_H

#define PRINT_MODE 0

#define BUFFLEN 2048
#define MAX_ARGS 16
#define FILE_MAX_CHUNK 16384

#define FILE_OK 150
#define FILE_TRANSFER_OK 226
#define PASV_OK 227
#define LOGIN_OK 230
#define LOGIN_ERR 530
#define CD_OK 250
#define CD_ERR 550
#define SESH_CLOSED 221

typedef void (*func_t)(int argc, char *argv[], void *ctx);

typedef struct
{
    const char *key;
    func_t value;
} dict_entry;

//shared context dump
typedef struct
{
    int s_socket;
    int resp_code;
    char local_path[BUFFLEN]; // local dir for io
    char remote_path[BUFFLEN]; // remote dir for io
} client_ctx;

typedef int (*tree_action_fn)(client_ctx *ctx, const char *path, bool is_dir); // for recursion

void get_input(char *inp_buffer, char *msg);

void send_command(int s_socket, char *command, char *args[]);

int recv_response(int s_socket, char buffer[BUFFLEN]);

void extract_pwd(char *resp, char *out, size_t out_len);

void switch_func(char *inp, void *ctx);

void open_data_connection(client_ctx *ctx, char *buffer, int *data_socket_num);
void close_data_connection(int data_socket);
void parse_list(char *list, char **files, int *file_count, char **folders, int *folder_count);

int delete_action(client_ctx *ctx, const char *path, bool is_dir);
int download_action(client_ctx *ctx, const char *path, bool is_dir);
int upload_recurse(client_ctx *ctx, const char *local_path, const char *remote_path);
int recurse_remote(client_ctx *ctx, const char *path, tree_action_fn action);

#endif // FTP_H