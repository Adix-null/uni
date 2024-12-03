#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#include "func.h"

static int errors = 0;

Node* create_node(char data[WORD_MAX])
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(new_node == NULL)
    {
        printf("Atminties alokacija nepavyko\n");
        errors++;
        return;
    }
    strcpy(new_node->data, data);
    //užpildo likusią vietą eilutėje su null reikšmėm
    memset(new_node->data + strlen(data), '\0', WORD_MAX - strlen(data));
    new_node->next = NULL;
    return new_node;
}

void append(Node** head, char data[WORD_MAX])
{
    Node* new_node = create_node(data);
    if(*head == NULL)
    {
        *head = new_node;
        return;
    }
    //eiti per nodeus kol bus pasiektas head galas
    Node* temp = *head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;
}

void generate_nodes(Node** head, int size, char init_val[WORD_MAX])
{
    for(int i = 0; i < size; i++)
    {
        append(head, init_val);
    }
}

Node* get_at_pos(Node** head, int pos)
{
    if (head == NULL)
    {
        return NULL;
    }

    Node* temp = *head;
    for(int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    return temp;
}

int list_size(Node* head)
{
    return head == NULL ? 0 : list_size(head->next) + 1;
}

void print_list(Node* head)
{
    if (head == NULL)
    {
        printf("NULL\n");
        return;
    }
    printf("%s -> ", head->data);
    print_list(head->next);
}

void delete_node(Node** head, char key[WORD_MAX])
{
    Node* temp = *head;
    Node* prev = NULL;

    //Jei reikia ištrinti patį headą
    if(temp != NULL && strcmp(temp->data, key) == 0)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while(temp != NULL && strcmp(temp->data, key) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("Reikšmė nesurasta\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void delete_list(Node** head)
{
    Node* temp = *head;
    Node* next_node = NULL;

    while(temp != NULL)
    {
        next_node = temp->next;
        free(temp);
        temp = next_node;
    }
    *head = NULL;
}

void read_from_file(Node** head, FILE *file, char* file_name)
{
    file = fopen(file_name, "r");
    char buffer[WORD_MAX];

    while (fscanf(file, "%255s", buffer) == 1)
    {
        append(head, buffer);
        if(buffer[254] != '\0')
        {
            printf("Žodis dalinamas\n");
            buffer[254] = '\0';
        }
    }

    fclose(file);
}

int warn(char* msg)
{
    int c;
    printf("%s", msg);
    scanf("%d", &c);
    return c == 1 ? 1 : 0;
}

void validate_input_int(char* inp_msg, char err_msg[][WORD_MAX], int *num, int min, int max)
{
    printf("%s", inp_msg);
    int result = 0;
    do
    {
        int scan_result = scanf("%d", num);

        if(*num < min)
        {
            result = 0;
        }
        else if(*num > max)
        {
            result = 1;
        }
        else
        {
            result = -1;
        }

        if(result != -1 && err_msg[result] != NULL)
        {
            if(scan_result != 1)
            {
                result  = 2;
                while((getchar()) != '\n');
            }
            printf("%s", err_msg[result]);
            printf("Pakartokite įvestį\n");
        }
    }
    while(result != -1);
}

void validate_input_string(char* inp_msg, char err_msg[][WORD_MAX], char* str[WORD_MAX], int max_length)
{
    printf("%s", inp_msg);
    int result = 0;
    do
    {
        scanf("%s", str);
        if(strlen(str) > max_length)
        {
            result = 0;
        }
        else
        {
            result = -1;
        }

        if(result != -1)
        {
            if(err_msg[result] != NULL)
            {
                printf("%s", err_msg[result]);
                printf("Pakartokite įvestį\n");
            }

        }
    }
    while(result != -1);
}

void validate_file(char err_msg[][WORD_MAX], char *op, FILE *file, char file_name[WORD_MAX])
{
    file = fopen(file_name, op);
    if (file == NULL)
    {
        printf("%s", err_msg[0]);
        errors++;
        return;
    }
    fclose(file);
}

