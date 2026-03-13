#ifndef FTP_H
#define FTP_H

#define PRINT_MODE 0

#define BUFFLEN 1024
#define MAX_ARGS 16

#define FILE_OK 150
#define FILE_TRANSFER_OK 226
#define PASV_OK 227
#define LOGIN_OK 230
#define LOGIN_ERR 530
#define CD_OK 250
#define CD_ERR 550
#define SESH_CLOSED 221

/*
https://www.rfc-editor.org/rfc/rfc959.html

5.3.1.  FTP COMMANDS

        The following are the FTP commands:

            USER <SP> <username> <CRLF>
            PASS <SP> <password> <CRLF>
            ACCT <SP> <account-information> <CRLF>
            CWD  <SP> <pathname> <CRLF>
            CDUP <CRLF>
            SMNT <SP> <pathname> <CRLF>
            QUIT <CRLF>
            REIN <CRLF>
            PORT <SP> <host-port> <CRLF>
            PASV <CRLF>
            TYPE <SP> <type-code> <CRLF>
            STRU <SP> <structure-code> <CRLF>
            MODE <SP> <mode-code> <CRLF>
            RETR <SP> <pathname> <CRLF>
            STOR <SP> <pathname> <CRLF>
            STOU <CRLF>
            APPE <SP> <pathname> <CRLF>
            ALLO <SP> <decimal-integer>
                [<SP> R <SP> <decimal-integer>] <CRLF>
            REST <SP> <marker> <CRLF>
            RNFR <SP> <pathname> <CRLF>
            RNTO <SP> <pathname> <CRLF>
            ABOR <CRLF>
            DELE <SP> <pathname> <CRLF>
            RMD  <SP> <pathname> <CRLF>
            MKD  <SP> <pathname> <CRLF>
            PWD  <CRLF>
            LIST [<SP> <pathname>] <CRLF>
            NLST [<SP> <pathname>] <CRLF>
            SITE <SP> <string> <CRLF>
            SYST <CRLF>
            STAT [<SP> <pathname>] <CRLF>
            HELP [<SP> <string>] <CRLF>
            NOOP <CRLF>
*/

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
} client_ctx;

void get_input(char *inp_buffer, char *msg);

void send_command(int s_socket, char *command, char *args[]);

int recv_response(int s_socket, char buffer[BUFFLEN]);

void extract_pwd(char *resp, char *out, size_t out_len);

void switch_func(char *inp, void *ctx);

void open_data_connection(client_ctx *ctx, char *buffer, int *data_socket_num);
void close_data_connection(int data_socket);
void parse_list(char *list, char **files, int *file_count, char **folders, int *folder_count);

int delete_action(client_ctx *ctx, const char *path, int is_dir);

void help(int argc, char *argv[], void *ctx);
void ls     (int argc, char *argv[], void *ctx);
void cd     (int argc, char *argv[], void *ctx);
void mkdir  (int argc, char *argv[], void *ctx);
void rm     (int argc, char *argv[], void *ctx);
void rmdir  (int argc, char *argv[], void *ctx);
void getfile(int argc, char *argv[], void *ctx);
void putfile(int argc, char *argv[], void *ctx);
void quit   (int argc, char *argv[], void *ctx);

#endif // FTP_H