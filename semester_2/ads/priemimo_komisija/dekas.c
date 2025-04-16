#include <stdio.h>
#include <stdlib.h>

#define DEKO_MAKS_ELEMENTU_KIEKIS 5
#define DEKU_MAKS_KIEKIS 3

static int deku_kiekis_atmintyje = 0;
static int error = 0;

char klaidu_zinutes[6][256] = {
    "Klaida nr. 1: Viršijama 3 dekų apimtis\n",
    "Klaida nr. 2: Deke nėra elementų\n",
    "Klaida nr. 3: Viršijama 5 dekų kiekio apimtis\n",
    "Klaida nr. 4: Netinkama pozicija deke\n",
    "Klaida nr. 5: Dekas nesukurtas\n",
    "Klaida nr. 6: Blogas deko skaičius\n"};

void throw_error(int kodas)
{
    printf("%s", klaidu_zinutes[kodas - 1]);
    error = 1;
}

typedef struct
{
    int *data;
    int front, back, size, capacity;
} Dequeue;

Dequeue *create_dequeue()
{
    if (deku_kiekis_atmintyje == DEKU_MAKS_KIEKIS)
    {
        throw_error(3);
    }
    if (error == 0)
    {
        deku_kiekis_atmintyje++;
        Dequeue *dekas = (Dequeue *)malloc(sizeof(Dequeue));
        dekas->capacity = DEKO_MAKS_ELEMENTU_KIEKIS;
        dekas->data = (int *)malloc(dekas->capacity * sizeof(int));
        dekas->front = dekas->back = dekas->size = 0;
        return dekas;
    }
    error = 0;
}

void push_front(Dequeue *dekas, int value)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (dekas->size == dekas->capacity)
    {
        throw_error(1);
    }
    if (error == 0)
    {
        dekas->front = (dekas->front - 1 + dekas->capacity) % dekas->capacity;
        dekas->data[dekas->front] = value;
        dekas->size++;
    }
    error = 0;
}

void push_back(Dequeue *dekas, int value)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (dekas->size == dekas->capacity)
    {
        throw_error(1);
    }
    if (error == 0)
    {
        dekas->data[dekas->back] = value;
        dekas->back = (dekas->back + 1) % dekas->capacity;
        dekas->size++;
    }
    error = 0;
}

int pop_front(Dequeue *dekas)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (dekas->size == 0)
    {
        throw_error(2);
    }
    if (error == 0)
    {
        int value = dekas->data[dekas->front];
        dekas->front = (dekas->front + 1) % dekas->capacity;
        dekas->size--;
        return value;
    }
    error = 0;
}

int pop_back(Dequeue *dekas)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (dekas->size == 0)
    {
        throw_error(2);
    }
    if (error == 0)
    {
        dekas->back = (dekas->back - 1 + dekas->capacity) % dekas->capacity;
        int value = dekas->data[dekas->back];
        dekas->size--;
        return value;
    }
    error = 0;
}

int top(Dequeue *dekas)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (dekas->size == 0)
    {
        throw_error(2);
    }
    if (error == 0)
    {
        return dekas->data[dekas->front];
    }
    error = 0;
}

int bottom(Dequeue *dekas)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (dekas->size == 0)
    {
        throw_error(2);
    }
    if (error == 0)
    {
        return dekas->data[(dekas->back - 1 + dekas->capacity) % dekas->capacity];
    }
    error = 0;
}

void print_dequeue(Dequeue *dekas)
{
    if (dekas == NULL || dekas->size == 0)
    {
        printf("Dekas tuščias\n");
    }
    else
    {
        printf("front ");
        for (int i = 0; i < dekas->size; i++)
        {
            printf("%d, ", dekas->data[(dekas->front + i) % dekas->capacity]);
        }
        printf("back\n");
    }
}

void free_dequeue(Dequeue *dekas)
{
    if (deku_kiekis_atmintyje == 0)
    {
        throw_error(5);
    }
    if (error == 0)
    {
        deku_kiekis_atmintyje--;
        free(dekas->data);
        // free(dekas);
        dekas = NULL;
    }
    error = 0;
}