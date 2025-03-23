#include "func.hpp"
#include <string>

namespace ip2
{
    class Dequeue
    {
    private:
        int *data;
        int front, back, size, capacity;

    public:
        Dequeue *create_dequeue()
        {
            if (dequeue_count == DEQUEUE_MAX_COUNT)
            {
                Exception e;
                e.throw_error(3);
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

        void push_front(int value)
        {
            if (this == NULL)
            {
                Exception e;
                e.throw_error(5);
            }
            if (this->size == this->capacity)
            {
                Exception e;
                e.throw_error(1);
            }
            if (error == 0)
            {
                this->front = (this->front - 1 + this->capacity) % this->capacity;
                this->data[this->front] = value;
                this->size++;
            }
            error = 0;
        }

        void push_back(int value)
        {
            if (this == NULL)
            {
                Exception e;
                e.throw_error(5);
            }
            if (this->size == this->capacity)
            {
                Exception e;
                e.throw_error(1);
            }
            if (error == 0)
            {
                this->data[this->back] = value;
                this->back = (this->back + 1) % this->capacity;
                this->size++;
            }
            error = 0;
        }

        int pop_front()
        {
            if (this == NULL)
            {
                Exception e;
                e.throw_error(5);
            }
            if (this->size == 0)
            {
                Exception e;
                e.throw_error(2);
            }
            if (error == 0)
            {
                int value = this->data[this->front];
                this->front = (this->front + 1) % this->capacity;
                this->size--;
                return value;
            }
            error = 0;
            return 0;
        }

        int pop_back()
        {
            if (this == NULL)
            {
                Exception e;
                e.throw_error(5);
            }
            if (this->size == 0)
            {
                Exception e;
                e.throw_error(2);
            }
            if (error == 0)
            {
                this->back = (this->back - 1 + this->capacity) % this->capacity;
                int value = this->data[this->back];
                this->size--;
                return value;
            }
            error = 0;
            return 0;
        }

        int top()
        {
            if (this == NULL)
            {
                Exception e;
                e.throw_error(5);
            }
            if (this->size == 0)
            {
                Exception e;
                e.throw_error(2);
            }
            if (error == 0)
            {
                return this->data[this->front];
            }
            error = 0;
            return 0;
        }

        int bottom()
        {
            if (this == NULL)
            {
                Exception e;
                e.throw_error(5);
            }
            if (this->size == 0)
            {
                Exception e;
                e.throw_error(2);
            }
            if (error == 0)
            {
                return this->data[(this->back - 1 + this->capacity) % this->capacity];
            }
            error = 0;
            return 0;
        }

        void insert(int index, int value)
        {
            if (this == NULL)
            {
                Exception e;
                e.throw_error(5);
            }
            if (index < 0 || index > this->size)
            {
                Exception e;
                e.throw_error(4);
            }
            if (this->size == this->capacity)
            {
                Exception e;
                e.throw_error(1);
            }
            for (int i = this->size; i > index; i--)
            {
                this->data[(this->front + i) % this->capacity] = this->data[(this->front + i - 1) % this->capacity];
            }
            if (error == 0)
            {
                this->data[(this->front + index) % this->capacity] = value;
                this->size++;
            }
            error = 0;
        }

        void print_dequeue()
        {
            if (this == NULL || this->size == 0)
            {
                Exception e;
                e.throw_error(2);
            }
            else
            {
                printf("Start ");
                for (int i = 0; i < this->size; i++)
                {
                    printf("%d, ", this->data[(this->front + i) % this->capacity]);
                }
                printf("End\n");
            }
        }

        ~Dequeue()
        {
            dequeue_count--;
        }
    };
    class Exception
    {
    private:
        std::string error_messages[6] = {
            "Error 1: Exceeded" + std::to_string(DEQUEUE_MAX_ELEMENT_COUNT) + " dequeue element count\n",
            "Error 2: Empty dequeue\n",
            "Error 3: Exceeded" + std::to_string(DEQUEUE_MAX_COUNT) + " dequeue count\n",
            "Error 4: Bad dequeue position\n",
            "Error 5: Dequeue is not initialized\n",
            "Error 6: Bad dequeue number\n"};

    public:
        void throw_error(int code)
        {
            printf("%s", error_messages[code - 1]);
        }
    };
}