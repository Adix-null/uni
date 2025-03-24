#include "func.hpp"
#include <string>
#include <iostream>

namespace ip2
{

    Dequeue *Dequeue::create_dequeue()
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

    void Dequeue::push_front(int value)
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

    void Dequeue::push_back(int value)
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

    int Dequeue::pop_front()
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

    int Dequeue::pop_back()
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

    int Dequeue::top()
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

    int Dequeue::bottom()
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

    void Dequeue::insert(int index, int value)
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

    void Dequeue::print_dequeue()
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

    ip2::Exception::Exception() // Initialize error messages in the constructor
    {
        error_messages[0] = "Error 1: Exceeded " + std::to_string(DEQUEUE_MAX_ELEMENT_COUNT) + " dequeue element count\n";
        error_messages[1] = "Error 2: Empty dequeue\n";
        error_messages[2] = "Error 3: Exceeded " + std::to_string(DEQUEUE_MAX_COUNT) + " dequeue count\n";
        error_messages[3] = "Error 4: Bad dequeue position\n";
        error_messages[4] = "Error 5: Dequeue is not initialized\n";
        error_messages[5] = "Error 6: Bad dequeue number\n";
    }

    void Exception::throw_error(int code)
    {
        if (code < 1 || code > 6) // Prevent out-of-bounds access
        {
            std::cerr << "Unknown error code: " << code << std::endl;
            return;
        }
        std::cerr << error_messages[code - 1];
    }
}