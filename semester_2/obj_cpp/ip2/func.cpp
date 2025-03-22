#include <func.hpp>

class Dequeue
{
private:
    int *data;
    int front, back, size, capacity;
    string error_messages[6] = {
        "Error 1: Exceeded" + to_string(DEQUEUE_MAX_ELEMENT_COUNT) + " dequeue element count\n",
        "Error 2: Empty dequeue\n",
        "Error 3: Exceeded" + to_string(DEQUEUE_MAX_COUNT) + " dequeue count\n",
        "Error 4: Bad dequeue position\n",
        "Error 5: Dequeue is not initialized\n",
        "Error 6: Bad dequeue number\n"};
    void throw_error(int kodas)
    {
        printf("%s", error_messages[kodas - 1]);
        error = 1;
    }

public:
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

    void free_mem(Dequeue *dequeue)
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

    ~Dequeue()
    {
        dequeue_count--;
    }
};