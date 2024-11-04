// LSP: 2413914
// el. pastas: adomas.bieliunas@mifstud.vu.lt
// 3 uzduotis, 4 variantas

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <string.h>

#define ROW_SIZE 257
#define SEPARATOR ' '

typedef struct
{
    char (*arr)[ROW_SIZE];
    int size;
} Stack;

void initStack(Stack *stack)
{
    stack->arr = (char(*)[ROW_SIZE])calloc(stack->size, ROW_SIZE);
    memset((*stack->arr), 0, stack->size);
}

void printStack(Stack *stack, FILE *file)
{
    for (int i = 0; i < stack->size; i++)
    {
        fprintf(file, "%s", stack->arr[i]);
    }
    fprintf(file, "\n");
}

void push(Stack *stack, char value[ROW_SIZE])
{
    stack->arr = realloc(stack->arr, (stack->size + 1) * ROW_SIZE);
    strncpy(stack->arr[stack->size], value, ROW_SIZE);
    ++(stack->size);
}

void destroyStack(Stack *stack)
{
    memset((*stack->arr), 0, stack->size);
    free(*stack->arr);
    stack->size = 0;
    stack = NULL;
}

void remove_extra_spaces(char *str)
{
    int x = 0;
    bool spaceFound = false;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ')
        {
            str[x] = str[i];
            x++;
            spaceFound = false;
        }
        else if (str[i] == ' ' && !spaceFound)
        {
            str[x] = str[i];
            x++;
            spaceFound = true;
        }
    }
    str[x] = '\0';
}

char *join_words(char line[ROW_SIZE])
{
    remove_extra_spaces(line);
    char *row;
    row = (char *)calloc(ROW_SIZE, sizeof(row[0]));
    memset(row, 0, ROW_SIZE);
    int cn = 0;

    for (int i = 0; i < ROW_SIZE - 2; i++, cn++)
    {
        row[cn] = line[i];
        if (line[i] == line[i + 2] && line[i + 1] == SEPARATOR)
        {
            i += 2;
        }
    }
    if (line[ROW_SIZE - 2] != ' ')
        row[cn] = line[ROW_SIZE - 2];
    if (line[ROW_SIZE - 1] != ' ')
        row[cn + 1] = line[ROW_SIZE - 1];
    return row;
}

void validate_file_name(char *msg, char *file_name, int file_name_size, FILE *stream)
{
    printf("%s", msg);
    fgets(file_name, file_name_size, stream);
    // replace \n with \0
    file_name[strcspn(file_name, "\n")] = '\0';
}

void validate_file(char *op, FILE *file, char *file_name, char *err_msg)
{
    file = fopen(file_name, op);
    if (file == NULL)
    {
        printf("%s", err_msg);
        exit(-1);
    }
}

void process_file(Stack *s, FILE *file)
{
    char line[ROW_SIZE] = {0};
    while (fgets(line, ROW_SIZE, file) != NULL)
    {
        if (line[ROW_SIZE - 2] != '\0')
        {
            line[ROW_SIZE - 2] = '\n';
            int ch;
            while ((ch = fgetc(file)) != '\n' && ch != EOF)
                ;
        }

        strcpy(line, join_words(line));
        push(s, line);
        memset(line, 0, ROW_SIZE);
    }
}

int main()
{
    Stack s = {0, 0};
    initStack(&s);

    FILE *file;
    char inp_file_name[64];
    char otp_file_name[64];

    char *err_inp = "Nepavyko atidaryti ivesties failo.\n";
    char *err_otp = "Nepavyko atidaryti isvesties failo.\n";
    char *msg_inp = "Ivesties failo pavadinimas:\n";
    char *msg_otp = "Isvesties failo pavadinimas:\n";

    validate_file_name(msg_inp, inp_file_name, sizeof(inp_file_name), stdin);
    validate_file_name(msg_otp, otp_file_name, sizeof(otp_file_name), stdin);

    validate_file("r", file, inp_file_name, err_inp);
    process_file(&s, file);
    fclose(file);

    validate_file("w", file, otp_file_name, err_otp);
    printStack(&s, file);
    fclose(file);

    destroyStack(&s);

    return 0;
}
