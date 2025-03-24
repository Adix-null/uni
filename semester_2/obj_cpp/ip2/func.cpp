#include <string>
#include <iostream>
#include "func.hpp"

namespace ip2
{
    class DequeueImpl
    {
    public:
        int *data;                       // The data of the dequeue, a list of numbers
        int front, back, size, capacity; // The neccessary data to describe the size and position of data

        DequeueImpl()
        {
            if (dequeue_count == DEQUEUE_MAX_COUNT)
            {
                Exception e;
                e.throw_error(3);
            }
            if (error == 0)
            {
                dequeue_count++;
                this->capacity = DEQUEUE_MAX_ELEMENT_COUNT;
                this->data = (int *)malloc(this->capacity * sizeof(int));
                this->front = this->back = this->size = 0;
            }
            error = 0;
        }

        DequeueImpl(const DequeueImpl &other) // THis one is for copying
        {
            this->capacity = other.capacity;
            this->size = other.size;
            this->front = other.front;
            this->back = other.back;
            this->data = new int[this->capacity]; // Deep copy the array

            for (int i = 0; i < this->size; i++)
            {
                this->data[(this->front + i) % this->capacity] = other.data[(other.front + i) % other.capacity];
            }
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

        DequeueImpl &operator=(const DequeueImpl &other)
        {
            if (this == &other)
                return *this;

            delete[] data;

            this->capacity = other.capacity;
            this->size = other.size;
            this->front = other.front;
            this->back = other.back;
            this->data = new int[this->capacity];

            for (int i = 0; i < this->size; i++)
            {
                this->data[(this->front + i) % this->capacity] = other.data[(other.front + i) % other.capacity];
            }

            return *this;
        }
        DequeueImpl operator+(const DequeueImpl &other)
        {
            if (this->size != other.size)
            {
                Exception e;
                e.throw_error(6);
                return *this;
            }

            DequeueImpl result;
            result.size = this->size;
            result.capacity = this->capacity;
            result.data = new int[result.capacity];

            for (int i = 0; i < this->size; i++)
            {
                result.data[(result.front + i) % result.capacity] =
                    this->data[(this->front + i) % this->capacity] +
                    other.data[(other.front + i) % other.capacity];
            }

            return result;
        }
        DequeueImpl operator-(const DequeueImpl &other)
        {
            if (this->size != other.size)
            {
                Exception e;
                e.throw_error(6);
                return *this;
            }
            DequeueImpl result;
            result.size = this->size;
            result.capacity = this->capacity;
            result.data = new int[result.capacity];

            for (int i = 0; i < this->size; i++)
            {
                result.data[(result.front + i) % result.capacity] =
                    this->data[(this->front + i) % this->capacity] -
                    other.data[(other.front + i) % other.capacity];
            }

            return result;
        }
        DequeueImpl operator*(const DequeueImpl &other)
        {
            if (this->size != other.size)
            {
                Exception e;
                e.throw_error(6);
                return *this;
            }

            DequeueImpl result;
            result.size = this->size;
            result.capacity = this->capacity;
            result.data = new int[result.capacity];

            for (int i = 0; i < this->size; i++)
            {
                result.data[(result.front + i) % result.capacity] =
                    this->data[(this->front + i) % this->capacity] *
                    other.data[(other.front + i) % other.capacity];
            }

            return result;
        }
        DequeueImpl operator/(const DequeueImpl &other)
        {
            if (this->size != other.size)
            {
                Exception e;
                e.throw_error(6);
                return *this;
            }

            DequeueImpl result;
            result.size = this->size;
            result.capacity = this->capacity;
            result.data = new int[result.capacity];

            for (int i = 0; i < this->size; i++)
            {
                result.data[(result.front + i) % result.capacity] =
                    this->data[(this->front + i) % this->capacity] -
                    other.data[(other.front + i) % other.capacity];
            }

            return result;
        }

        DequeueImpl &operator+=(const DequeueImpl &other)
        {
            *this = *this + other;
            return *this;
        }
        DequeueImpl &operator-=(const DequeueImpl &other)
        {
            *this = *this - other;
            return *this;
        }
        DequeueImpl &operator*=(const DequeueImpl &other)
        {
            *this = *this * other;
            return *this;
        }
        DequeueImpl &operator/=(const DequeueImpl &other)
        {
            *this = *this / other;
            return *this;
        }

        bool operator==(const DequeueImpl &other) const
        {
            if (this->size != other.size || this->capacity != other.capacity)
                return false;

            for (int i = 0; i < this->size; i++)
            {
                if (this->data[(this->front + i) % this->capacity] !=
                    other.data[(other.front + i) % other.capacity])
                {
                    return false;
                }
            }
            return true;
        }
        bool operator!=(const DequeueImpl &other) const
        {
            return !(*this == other);
        }
        bool operator>(const DequeueImpl &other) const
        {
            return this->size > other.size;
        }
        bool operator<(const DequeueImpl &other) const
        {
            return this->size < other.size;
        }
        bool operator>=(const DequeueImpl &other) const
        {
            return this->size >= other.size;
        }
        bool operator<=(const DequeueImpl &other) const
        {
            return this->size <= other.size;
        }

        void operator!()
        {
            if (this->data != nullptr)
            {
                free(this->data);
                this->data = (int *)calloc(this->capacity, sizeof(int));
            }
            this->front = this->back = this->size = 0;
        }
        int operator[](const int value) const
        {
            for (int i = 0; i < this->size; i++)
            {
                if (this->data[(this->front + i) % this->capacity] == value)
                    return i;
            }
            return -1;
        }
    };

    // Boilerplate galore

    Dequeue::Dequeue()
    {
        impl = new DequeueImpl();
    }
    Dequeue::~Dequeue()
    {
        dequeue_count--;
        delete impl;
    }

    void Dequeue::push_front(int value)
    {
        impl->push_front(value);
    }
    void Dequeue::push_back(int value)
    {
        impl->push_back(value);
    }
    int Dequeue::pop_front()
    {
        return impl->pop_front();
    }
    int Dequeue::pop_back()
    {
        return impl->pop_back();
    }
    int Dequeue::top()
    {
        return impl->top();
    }
    int Dequeue::bottom()
    {
        return impl->bottom();
    }
    void Dequeue::insert(int index, int value)
    {
        impl->insert(index, value);
    }
    void Dequeue::print_dequeue()
    {
        impl->print_dequeue();
    }

    Dequeue &Dequeue::operator=(const Dequeue &other)
    {
        if (this == &other) // Handle self-assignment
            return *this;

        *(this->impl) = *(other.impl);
        return *this;
    }
    Dequeue Dequeue::operator+(const Dequeue &other)
    {
        Dequeue result;
        result.impl = new DequeueImpl(*(this->impl) + *(other.impl));
        return result;
    }
    Dequeue Dequeue::operator-(const Dequeue &other)
    {
        Dequeue result;
        result.impl = new DequeueImpl(*(this->impl) - *(other.impl));
        return result;
    }
    Dequeue Dequeue::operator*(const Dequeue &other)
    {
        Dequeue result;
        result.impl = new DequeueImpl(*(this->impl) * *(other.impl));
        return result;
    }
    Dequeue Dequeue::operator/(const Dequeue &other)
    {
        Dequeue result;
        result.impl = new DequeueImpl(*(this->impl) / *(other.impl));
        return result;
    }

    Dequeue &Dequeue::operator+=(const Dequeue &other)
    {
        *this->impl += *other.impl;
        return *this;
    }
    Dequeue &Dequeue::operator-=(const Dequeue &other)
    {
        *this->impl -= *other.impl;
        return *this;
    }
    Dequeue &Dequeue::operator*=(const Dequeue &other)
    {
        *this->impl *= *other.impl;
        return *this;
    }
    Dequeue &Dequeue::operator/=(const Dequeue &other)
    {
        *this->impl /= *other.impl;
        return *this;
    }

    bool Dequeue::operator==(const Dequeue &other) const
    {
        return *(this->impl) == *(other.impl);
    }
    bool Dequeue::operator!=(const Dequeue &other) const
    {
        return *(this->impl) != *(other.impl);
    }
    bool Dequeue::operator>(const Dequeue &other) const
    {
        return *(this->impl) > *(other.impl);
    }
    bool Dequeue::operator<(const Dequeue &other) const
    {
        return *(this->impl) < *(other.impl);
    }
    bool Dequeue::operator>=(const Dequeue &other) const
    {
        return *(this->impl) >= *(other.impl);
    }
    bool Dequeue::operator<=(const Dequeue &other) const
    {
        return *(this->impl) <= *(other.impl);
    }

    void Dequeue::operator!() const
    {
        !(*impl);
    }
    int Dequeue::operator[](const int value) const
    {
        return (*impl)[value];
    }

    Exception::Exception() // Initialize error messages in the constructor
    {
        error_messages[0] = "Error 1: Exceeded " + std::to_string(DEQUEUE_MAX_ELEMENT_COUNT) + " dequeue element count\n";
        error_messages[1] = "Error 2: Empty dequeue\n";
        error_messages[2] = "Error 3: Exceeded " + std::to_string(DEQUEUE_MAX_COUNT) + " dequeue count\n";
        error_messages[3] = "Error 4: Bad dequeue position\n";
        error_messages[4] = "Error 5: Dequeue is not initialized\n";
        error_messages[5] = "Error 6: Dequeue sizes do not match\n";
    }

    const char *Exception::what() const noexcept
    {
        return "An exception has occurred in the dequeue\n";
    }

    void Exception::throw_error(int code)
    {
        if (code < 1 || code > 6)
        {
            std::cerr << "Unknown error code: " << code << std::endl;
            return;
        }
        std::cerr << error_messages[code - 1];
    }
}