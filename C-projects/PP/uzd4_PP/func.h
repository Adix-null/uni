#define WORD_MAX 256
#define LENGTH_MAX 100
#ifndef TESTING
#define TESTING 0
#endif

typedef struct Node
{
    char data[WORD_MAX];
    struct Node* next;
} Node;

Node* create_node(char [WORD_MAX]);

void append(Node**, char [WORD_MAX]);

void generate_nodes(Node**, int, char [WORD_MAX]);

Node* get_at_pos(Node**, int);

int list_size(Node*);

void print_list(Node*);

void delete_node(Node**, char [WORD_MAX]);

void delete_list(Node**);

void read_from_file(Node**, FILE *, char*);

int warn(char*);

void validate_input_int(char*, char [][WORD_MAX], int *, int, int);

void validate_input_string(char*, char [][WORD_MAX], char* [WORD_MAX], int);

void validate_file(char* inp_msg, char err_msg[][WORD_MAX], char *op, FILE *file, char file_name[WORD_MAX]);
