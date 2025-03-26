#include <string>
#include <iostream>
#include <functional>
#include "func.hpp"

namespace ip2
{
    void Dequeue::testForExceptions(const bool (&arr)[3])
    {
        if (arr[0] && impl == NULL)
        {
            throw UninitializedDequeueException();
        }
        if (arr[1] && impl->size == impl->capacity)
        {
            throw ExceededElementCountException();
        }
        if (arr[2] && impl->size == 0)
        {
            throw EmptyDequeueException();
        }
    }

    Dequeue::Dequeue()
    {
        impl = new DequeueImpl();
        if (dequeue_count == DEQUEUE_MAX_COUNT)
        {
            throw ExceededDequeueCountException();
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

    Dequeue::~Dequeue()
    {
        dequeue_count--;
        delete[] impl->data;
        delete impl;
    }

    void Dequeue::push_front(int value)
    {
        testForExceptions({true, true, false});
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
        testForExceptions({true, true, false});
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
        testForExceptions({true, false, true});
        if (error == 0)
        {
            int value = top();
            impl->front = (impl->front + 1) % impl->capacity;
            impl->size--;
            return value;
        }
        error = 0;
        return 0;
    }
    int Dequeue::pop_back()
    {
        testForExceptions({true, false, true});
        if (error == 0)
        {
            int value = bottom();
            impl->back = (impl->back + 1 + impl->size) % impl->capacity;
            impl->size--;
            return value;
        }
        error = 0;
        return 0;
    }
    int Dequeue::top()
    {
        testForExceptions({true, false, true});
        if (error == 0)
        {
            return impl->data[impl->front % impl->capacity];
        }
        error = 0;
        return 0;
    }
    int Dequeue::bottom()
    {
        testForExceptions({true, false, true});
        if (error == 0)
        {
            return impl->data[(impl->front + impl->size - 1) % impl->capacity];
        }
        error = 0;
        return 0;
    }
    void Dequeue::print_dequeue()
    {
        testForExceptions({true, false, true});
        if (error == 0)
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
    Dequeue Dequeue::arithmeticOperation(const Dequeue &other, Op op) const
    {
        if (impl->size != other.impl->size)
        {
            throw MismatchedDequeueSizesException();
        }

        Dequeue result;
        result.impl->size = impl->size;
        result.impl->capacity = impl->capacity;
        result.impl->data = new int[result.impl->capacity];

        for (int i = 0; i < impl->size; ++i)
        {
            result.impl->data[(result.impl->front + i) % result.impl->capacity] =
                op(impl->data[(impl->front + i) % impl->capacity],
                   other.impl->data[(other.impl->front + i) % other.impl->capacity]);
        }

        return result;
    }

    Dequeue Dequeue::operator+(const Dequeue &other)
    {
        return arithmeticOperation(other, std::plus<int>{});
    }
    Dequeue Dequeue::operator-(const Dequeue &other)
    {
        return arithmeticOperation(other, std::minus<int>{});
    }
    Dequeue Dequeue::operator*(const Dequeue &other)
    {
        return arithmeticOperation(other, std::multiplies<int>{});
    }
    Dequeue Dequeue::operator/(const Dequeue &other)
    {
        return arithmeticOperation(other, std::divides<int>{});
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

        result.impl->data = new int[result.impl->capacity];

        int j = 0;
        for (int i = 0; i < impl->size; ++i, ++j)
        {
            result.impl->data[j % result.impl->capacity] = impl->data[(i + impl->front) % impl->capacity];
        }

        for (int i = 0; i < other.impl->size; ++i, ++j)
        {
            result.impl->data[j % result.impl->capacity] = other.impl->data[(i + other.impl->front) % other.impl->capacity];
        }
        result.impl->front = 0;
        result.impl->back = j % result.impl->capacity;

        return result;
    }
    Dequeue &Dequeue::operator&=(const Dequeue &other)
    {
        *this = *this & other;
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
}