#include <stdio.h>
#include <stdlib.h>
#include <string>

#define DEQUEUE_MAX_ELEMENT_COUNT 5
#define DEQUEUE_MAX_COUNT 3

using namespace std;

static int dequeue_count = 0;
static int error = 0;

string error_messages[6] = {
    "Error 1: Exceeded " + to_string(DEQUEUE_MAX_ELEMENT_COUNT) + " dequeue element count\n",
    "Error 2: Empty dequeue\n",
    "Error 3: Exceeded " + to_string(DEQUEUE_MAX_COUNT) + " dequeue count\n",
    "Error 4: Bad dequeue position\n",
    "Error 5: Dequeue is not initialized\n",
    "Error 6: Bad dequeue number\n"};

void throw_error(int kodas)
{
    printf("%s", error_messages[kodas - 1]);
    error = 1;
}

typedef struct
{
    int *data;
    int front, back, size, capacity;
} Dequeue;

Dequeue *create_dequeue()
{
    if (dequeue_count == DEQUEUE_MAX_COUNT)
    {
        throw_error(3);
    }
    if (error == 0)
    {
        dequeue_count++;
        Dequeue *dequeue = (Dequeue *)malloc(sizeof(Dequeue));
        dequeue->capacity = DEQUEUE_MAX_ELEMENT_COUNT;
        dequeue->data = (int *)malloc(dequeue->capacity * sizeof(int));
        dequeue->front = dequeue->back = dequeue->size = 0;
        return dequeue;
    }
    error = 0;
    return NULL;
}

void push_front(Dequeue *dequeue, int value)
{
    if (dequeue == NULL)
    {
        throw_error(5);
    }
    if (dequeue->size == dequeue->capacity)
    {
        throw_error(1);
    }
    if (error == 0)
    {
        dequeue->front = (dequeue->front - 1 + dequeue->capacity) % dequeue->capacity;
        dequeue->data[dequeue->front] = value;
        dequeue->size++;
    }
    error = 0;
}

void push_back(Dequeue *dequeue, int value)
{
    if (dequeue == NULL)
    {
        throw_error(5);
    }
    if (dequeue->size == dequeue->capacity)
    {
        throw_error(1);
    }
    if (error == 0)
    {
        dequeue->data[dequeue->back] = value;
        dequeue->back = (dequeue->back + 1) % dequeue->capacity;
        dequeue->size++;
    }
    error = 0;
}

int pop_front(Dequeue *dequeue)
{
    if (dequeue == NULL)
    {
        throw_error(5);
    }
    if (dequeue->size == 0)
    {
        throw_error(2);
    }
    if (error == 0)
    {
        int value = dequeue->data[dequeue->front];
        dequeue->front = (dequeue->front + 1) % dequeue->capacity;
        dequeue->size--;
        return value;
    }
    error = 0;
    return 0;
}

int pop_back(Dequeue *dequeue)
{
    if (dequeue == NULL)
    {
        throw_error(5);
    }
    if (dequeue->size == 0)
    {
        throw_error(2);
    }
    if (error == 0)
    {
        dequeue->back = (dequeue->back - 1 + dequeue->capacity) % dequeue->capacity;
        int value = dequeue->data[dequeue->back];
        dequeue->size--;
        return value;
    }
    error = 0;
    return 0;
}

int top(Dequeue *dequeue)
{
    if (dequeue == NULL)
    {
        throw_error(5);
    }
    if (dequeue->size == 0)
    {
        throw_error(2);
    }
    if (error == 0)
    {
        return dequeue->data[dequeue->front];
    }
    error = 0;
    return 0;
}

int bottom(Dequeue *dequeue)
{
    if (dequeue == NULL)
    {
        throw_error(5);
    }
    if (dequeue->size == 0)
    {
        throw_error(2);
    }
    if (error == 0)
    {
        return dequeue->data[(dequeue->back - 1 + dequeue->capacity) % dequeue->capacity];
    }
    error = 0;
    return 0;
}

void insert(Dequeue *dequeue, int index, int value)
{
    if (dequeue == NULL)
    {
        throw_error(5);
    }
    if (index < 0 || index > dequeue->size)
    {
        throw_error(4);
    }
    if (dequeue->size == dequeue->capacity)
    {
        throw_error(1);
    }
    for (int i = dequeue->size; i > index; i--)
    {
        dequeue->data[(dequeue->front + i) % dequeue->capacity] = dequeue->data[(dequeue->front + i - 1) % dequeue->capacity];
    }
    if (error == 0)
    {
        dequeue->data[(dequeue->front + index) % dequeue->capacity] = value;
        dequeue->size++;
    }
    error = 0;
}

void print_dequeue(Dequeue *dequeue)
{
    if (dequeue == NULL || dequeue->size == 0)
    {
        throw_error(2);
    }
    else
    {
        printf("Start ");
        for (int i = 0; i < dequeue->size; i++)
        {
            printf("%d, ", dequeue->data[(dequeue->front + i) % dequeue->capacity]);
        }
        printf("End\n");
    }
}

void free(Dequeue *dequeue)
{
    if (dequeue_count == 0)
    {
        throw_error(5);
    }
    if (error == 0)
    {
        dequeue_count--;
        free(dequeue->data);
        // free(dequeue);
        dequeue = NULL;
    }
    error = 0;
}

int main()
{
    int loop = 0;
    int deko_sk = 1;
    static Dequeue *dekai[DEQUEUE_MAX_COUNT] = {NULL};

    while (loop == 0)
    {
        int choice = 0;
        printf("Meniu:\n");
        printf(" 1: Sukurti deką\n");
        printf(" 2: Įdėti elementą\n");
        printf(" 3: Push iš priekio\n");
        printf(" 4: Push iš galo\n");
        printf(" 5: Pop iš priekio\n");
        printf(" 6: Pop iš galo\n");
        printf(" 7: Top\n");
        printf(" 8: Bottom\n");
        printf(" 9: Atspausdinti deką\n");
        printf("10: Sunaikinti deką\n");
        printf("11: Pasirinkti deką\n");
        printf("12: Išeiti iš programos\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            dekai[deko_sk - 1] = create_dequeue();
            break;
        }
        case 2:
        {
            int v = 0;
            int i = 0;
            printf("Įveskite poziciją: ");
            scanf("%d", &i);
            printf("Įveskite reikšmę: ");
            scanf("%d", &v);
            insert(dekai[deko_sk - 1], i, v);
            break;
        }
        case 3:
        {
            int v = 0;
            printf("Įveskite reikšmę: ");
            scanf("%d", &v);
            push_front(dekai[deko_sk - 1], v);
            break;
        }
        case 4:
        {
            int v = 0;
            printf("Įveskite reikšmę: ");
            scanf("%d", &v);
            push_back(dekai[deko_sk - 1], v);
            break;
        }
        case 5:
        {
            printf("Pop priekis: %d\n", pop_front(dekai[deko_sk - 1]));
            break;
        }
        case 6:
        {
            printf("Pop galas: %d\n", pop_back(dekai[deko_sk - 1]));
            break;
        }
        case 7:
        {
            printf("Top: %d\n", top(dekai[deko_sk - 1]));
            break;
        }
        case 8:
        {
            printf("Bottom: %d\n", bottom(dekai[deko_sk - 1]));
            break;
        }
        case 9:
        {
            print_dequeue(dekai[deko_sk - 1]);
            break;
        }
        case 10:
        {
            free(dekai[deko_sk - 1]);
            break;
        }
        case 11:
        {
            printf("Įveskite deko numerį: ");
            scanf("%d", &deko_sk);
            if (deko_sk < 1 || deko_sk > DEQUEUE_MAX_COUNT)
            {
                throw_error(6);
            }
            break;
        }
        case 12:
        {
            loop = 1;
            break;
        }
        }
    }
    return 0;
}