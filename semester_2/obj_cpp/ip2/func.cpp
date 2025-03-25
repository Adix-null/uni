#include <string>
#include <iostream>
#include <functional>
#include "func.hpp"

namespace ip2
{
    Dequeue::Dequeue()
    {
        impl = new DequeueImpl();
        if (dequeue_count == DEQUEUE_MAX_COUNT)
        {
            DequeueException e;
            e.throw_error(3);
        }
        if (error == 0)
        {
            dequeue_count++;
            impl->capacity = DEQUEUE_MAX_ELEMENT_COUNT;
            impl->data = new int[impl->capacity];
            impl->front = impl->back = impl->size = 0;
        }
        error = 0;
    }
    Dequeue::~Dequeue()
    {
        dequeue_count--;
        delete[] impl->data;
        delete impl;
    }
    Dequeue::Dequeue(const Dequeue &other)
    {
        impl = new DequeueImpl();
        impl->capacity = other.impl->capacity;
        impl->size = other.impl->size;
        impl->front = other.impl->front;
        impl->back = other.impl->back;

        impl->data = new int[impl->capacity];
        for (int i = 0; i < impl->capacity; ++i)
        {
            impl->data[i] = other.impl->data[i];
        }
    }
    Dequeue &Dequeue::operator=(const Dequeue &other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] impl->data;
        delete impl;

        // Deep copy
        impl = new DequeueImpl();
        impl->capacity = other.impl->capacity;
        impl->size = other.impl->size;
        impl->front = other.impl->front;
        impl->back = other.impl->back;

        impl->data = new int[impl->capacity];
        for (int i = 0; i < impl->capacity; ++i)
        {
            impl->data[i] = other.impl->data[i];
        }

        return *this;
    }

    void Dequeue::push_front(int value)
    {
        if (impl == NULL)
        {
            DequeueException e;
            e.throw_error(5);
        }
        if (impl->size == impl->capacity)
        {
            DequeueException e;
            e.throw_error(1);
        }
        if (error == 0)
        {
            impl->front = (impl->front - 1 + impl->capacity) % impl->capacity;
            impl->data[impl->front] = value;
            impl->size++;
        }
        error = 0;
    }
    void Dequeue::push_back(int value)
    {
        if (impl == NULL)
        {
            DequeueException e;
            e.throw_error(5);
        }
        if (impl->size == impl->capacity)
        {
            DequeueException e;
            e.throw_error(1);
        }
        if (error == 0)
        {
            impl->data[impl->back] = value;
            impl->back = (impl->back + 1) % impl->capacity;
            impl->size++;
        }
        error = 0;
    }
    int Dequeue::pop_front()
    {
        if (impl == NULL)
        {
            DequeueException e;
            e.throw_error(5);
        }
        if (impl->size == 0)
        {
            DequeueException e;
            e.throw_error(2);
        }
        if (error == 0)
        {
            int value = impl->data[impl->front];
            impl->front = (impl->front + 1) % impl->capacity;
            impl->size--;
            return value;
        }
        error = 0;
        return 0;
    }
    int Dequeue::pop_back()
    {
        if (impl == NULL)
        {
            DequeueException e;
            e.throw_error(5);
        }
        if (impl->size == 0)
        {
            DequeueException e;
            e.throw_error(2);
        }
        if (error == 0)
        {
            impl->back = (impl->back - 1 + impl->capacity) % impl->capacity;
            int value = impl->data[impl->back];
            impl->size--;
            return value;
        }
        error = 0;
        return 0;
    }
    int Dequeue::top()
    {
        if (impl == NULL)
        {
            DequeueException e;
            e.throw_error(5);
        }
        if (impl->size == 0)
        {
            DequeueException e;
            e.throw_error(2);
        }
        if (error == 0)
        {
            return impl->data[impl->front % impl->capacity];
        }
        error = 0;
        return 0;
    }
    int Dequeue::bottom()
    {
        if (impl == NULL)
        {
            DequeueException e;
            e.throw_error(5);
        }
        if (impl->size == 0)
        {
            DequeueException e;
            e.throw_error(2);
        }
        if (error == 0)
        {
            return impl->data[(impl->back - 1 + impl->size) % impl->capacity];
        }
        error = 0;
        return 0;
    }
    void Dequeue::print_dequeue()
    {
        if (impl == NULL || impl->size == 0)
        {
            DequeueException e;
            e.throw_error(2);
        }
        else
        {
            std::cout << "Start ";
            for (int i = 0; i < impl->size; i++)
            {
                std::cout << impl->data[(impl->front + i) % impl->capacity] << ", ";
            }
            std::cout << "End\n";
        }
    }

    template <typename Op>
    Dequeue operate(const Dequeue &other, Op op)
    {
        if (impl->size != other.impl->size)
        {
            DequeueException e;
            e.throw_error(6);
            return *this;
        }

        Dequeue result;
        result.impl->size = impl->size;
        result.impl->capacity = impl->capacity;
        result.impl->data = new int[result.impl->capacity];

        for (int i = 0; i < impl->size; i++)
        {
            result.impl->data[i] =
                op(impl->data[i], other.impl->data[i]);
        }

        return result;
    }

    Dequeue Dequeue::operator+(const Dequeue &other)
    {
        return operate(other, std::plus<int>());
    }
    Dequeue Dequeue::operator-(const Dequeue &other)
    {
        return operate(other, std::minus<int>());
    }
    Dequeue Dequeue::operator*(const Dequeue &other)
    {
        return operate(other, std::multiplies<int>());
    }
    Dequeue Dequeue::operator/(const Dequeue &other)
    {
        return operate(other, std::divides<int>());
    }

    Dequeue &Dequeue::operator+=(const Dequeue &other)
    {
        *this = *this + other;
        return *this;
    }
    Dequeue &Dequeue::operator-=(const Dequeue &other)
    {
        *this = *this - other;
        return *this;
    }
    Dequeue &Dequeue::operator*=(const Dequeue &other)
    {
        *this = *this * other;
        return *this;
    }
    Dequeue &Dequeue::operator/=(const Dequeue &other)
    {
        *this = *this / other;
        return *this;
    }

    void Dequeue::operator+(int value)
    {
        push_front(value);
    }
    int Dequeue::operator++()
    {
        return pop_front();
    }
    void Dequeue::operator-(int value)
    {
        push_back(value);
    }
    int Dequeue::operator--()
    {
        return pop_back();
    }

    Dequeue Dequeue::operator&(const Dequeue &other)
    {
        if (impl->size == 0)
            return other;
        if (other.impl->size == 0)
            return *this;

        Dequeue result;
        result.impl->capacity = impl->capacity + other.impl->capacity;
        result.impl->size = impl->size + other.impl->size;
        result.impl->front = impl->front;
        result.impl->back = other.impl->back;

        result.impl->data = new int[result.impl->capacity];

        int j = 0;
        for (int i = impl->front; i < impl->capacity; ++i, ++j)
        {
            result.impl->data[j] = impl->data[i];
        }

        for (int i = other.impl->front; i < other.impl->capacity; ++i, ++j)
        {
            result.impl->data[j] = other.impl->data[i];
        }

        return result;
    }
    Dequeue &Dequeue::operator&=(const Dequeue &other)
    {
        return *this = *this & other;
        return *this;
    }

    bool Dequeue::equals(const Dequeue &other)
    {
        if (impl->size != other.impl->size || impl->capacity != other.impl->capacity)
            return false;

        for (int i = 0; i < impl->size; i++)
        {
            if (impl->data[(impl->front + i) % impl->capacity] !=
                other.impl->data[(other.impl->front + i) % other.impl->capacity])
            {
                return false;
            }
        }
        return true;
    }

    bool Dequeue::operator==(const Dequeue &other) const
    {
        return impl->size == other.impl->size;
    }
    bool Dequeue::operator!=(const Dequeue &other) const
    {
        return impl->size != other.impl->size;
    }
    bool Dequeue::operator>(const Dequeue &other) const
    {
        return impl->size > other.impl->size;
    }
    bool Dequeue::operator<(const Dequeue &other) const
    {
        return impl->size < other.impl->size;
    }
    bool Dequeue::operator>=(const Dequeue &other) const
    {
        return impl->size >= other.impl->size;
    }
    bool Dequeue::operator<=(const Dequeue &other) const
    {
        return impl->size <= other.impl->size;
    }

    void Dequeue::operator!() const
    {
        if (impl->data != nullptr)
        {
            free(impl->data);
            impl->data = (int *)calloc(impl->capacity, sizeof(int));
        }
        impl->front = impl->back = impl->size = 0;
    }
    bool Dequeue::operator[](const int value) const
    {
        for (int i = 0; i < impl->size; i++)
        {
            if (impl->data[(impl->front + i) % impl->capacity] == value)
                return true;
        }
        return false;
    }

    DequeueException::DequeueException() // Initialize error messages in the constructor
    {
        error_messages[0] = "Error 1: Exceeded " + std::to_string(DEQUEUE_MAX_ELEMENT_COUNT) + " dequeue element count\n";
        error_messages[1] = "Error 2: Empty dequeue\n";
        error_messages[2] = "Error 3: Exceeded " + std::to_string(DEQUEUE_MAX_COUNT) + " dequeue count\n";
        error_messages[3] = "Error 4: Bad dequeue position\n";
        error_messages[4] = "Error 5: Dequeue is not initialized\n";
        error_messages[5] = "Error 6: Dequeue sizes do not match\n";
    }

    const char *DequeueException::what() const noexcept
    {
        return "An exception has occurred in the dequeue\n";
    }

    void DequeueException::throw_error(int code)
    {
        if (code < 1 || code > 6)
        {
            std::cerr << "Unknown error code: " << code << std::endl;
            return;
        }
        std::cerr << error_messages[code - 1];
    }
}