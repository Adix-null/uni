#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define WORD_MAX 255
#define LENGTH_MAX 100

//redo everything with linked list :D

typedef struct Node
{
    char data[WORD_MAX];
    struct Node* next;
} Node;

Node* create_node(char data[WORD_MAX])
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(new_node == NULL)
    {
        printf("Atminties alokacija nepavyko\n");
        exit(1);
    }
    //strcpy(array[i], def);
        //užpildo likusią vietą eilutėje su null reikšmėm
        //memset(array[i] + strlen(def), '\0', WORD_MAX - strlen(def));
    strcpy(new_node->data, data);
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
    //Node* temp = head;
    for(int i = 0; i < size; i++)
    {
        append(head, init_val);
    }
}

void print_at_pos(Node** head, int pos)
{
    Node* temp = head;
    for(int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    printf("Elementas %d pozicijoje: %s\n", pos + 1, temp->data);
}

int list_size(Node** head)
{
    int count  = 0;
    Node* temp = head;
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

void print_list(Node* head)
{
    Node* temp = head;
    while(temp != NULL)
    {
        printf("%s -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


void delete_node(Node** head, char key[WORD_MAX])
{
    Node* temp = *head;
    Node* prev = NULL;

    //Jei reikia ištrinti patį headą
    if(temp != NULL &&strcmp(temp->data, key))
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while(temp != NULL && strcmp(temp->data, key))
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

//netinka atskira evaluator funkcija nes C nesuportina dinaminiu argumentu funkciju iskvietimuose

void validate_input_int(char* inp_msg, char err_msg[][WORD_MAX], int *num, int min, int max)
{
    printf("%s", inp_msg);
    int result = 0;
    do
    {
        scanf("%d", num);
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


int main()
{
    Node* head = NULL;
    /*
    int size = 0;

    printf("Linked List: ");
    append(&head, "test1");
    append(&head, "test2");
    append(&head, "0V");

    print_list(head);

    delete_node(&head, "0V");
    printf("Linked List after deletion: ");
    print_list(head);

    printf("Size: %d\n", list_size(head));
    */

    printf("Aprašas:\n");
    printf("Programa atlieka veiksmus su sąrašu, kurio 1 elemetas yra simbolių eilutė. \
    Eilutės maksimalus ilgis - 255 simboliai. Toliau pateikiama vartotojo pasirinkimo meniu, jam reikia įvesti vieną skaičių. \
    Įvedus kelis skaičius iš karto bus vykdoma tik komanda, susieta su 1 įvestu skaitmeniu.\n");

    int loop = 0;
    while(loop == 0)
    {
        int choice = 0;
        printf("Meniu:\n");
        printf("1 - sukuriamas tuščias sąrašas\n");
        printf("2 - sukuriamas sąrašas su pradine reikšme visose pozicijose\n");
        printf("3 - nuskaitomi duomenys iš duomenų failo į visą sąrašą\n");
        printf("4 - spausdinamas elementas nurodytoje pozicijoje\n");
        printf("5 - spausdinamas visas sąrašas\n");
        printf("6 - ištrinamas visas sąrašas\n");
        printf("7 - išeinama iš programos\n");
        printf("Parinktis:\n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                int size = 0;

                char error_msgs[2][WORD_MAX] = {
                "Skaičius per mažas\n",
                "Skaičius per didelis\n",
                };

                validate_input_int("Sąrašo ilgis:\n", error_msgs, &size, 1, LENGTH_MAX);

                generate_nodes(&head, size, "\0");
                break;
            }

            case 2:
            {
                int size = 0;
                char init_val[WORD_MAX];

                char error_msgs_int[2][WORD_MAX] = {
                "Skaičius per mažas\n",
                "Skaičius per didelis\n",
                };
                char error_msgs_string[2][WORD_MAX] = {
                "Eilutės ilgis per didelis\n"
                };

                validate_input_int("Sąrašo ilgis:\n", error_msgs_int, &size, 1, LENGTH_MAX);
                validate_input_string("Pradinė reikšmė:\n", error_msgs_string, &init_val, WORD_MAX);
                generate_nodes(&head, size, init_val);
                break;
            }

            case 3:
            {

                break;
            }

            case 4:
            {
                int pos = 0;

                char error_msgs_int[2][WORD_MAX] = {
                "Skaičius per mažas\n",
                "Skaičius per didelis\n",
                };
                validate_input_int("Elemento pozicija:\n", error_msgs_int, &pos, 1, list_size(head));

                print_at_pos(head, pos - 1);
                break;
            }

            case 5:
            {
                print_list(head);
                break;
            }

            case 6:
            {

                break;
            }

            case 7:
            {
                loop = 1;
                break;
            }
        }
    }
    return 0;

    char* name;
    FILE* file;
    file = fopen(name, "r+");

    return 0;
}
