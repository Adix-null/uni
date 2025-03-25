// Adomas Bieliūnas 1k 2.1gr
// camelCase, klasės pavadinimai iš didžiosios raidės, kintamųjų ir funkcijų iš mažosios

// Dequeue (Double-ended queue) is a primitive data type that I have implemented in C.
// Capacity and amount of dequeue sizes at any given point can be chosen arbitrarily.
// There is also another class, Exception, to handle errors.
// Makefile commands:
// make — Builds everything
// make build — Builds the main executable
// make run — Runs the main executable
// make build_run — Builds and runs the main executable
// make test_build — Builds the test executable
// make test_run — Runs the test executable
// make test_build_run — Builds and runs the test executable
// make clean — Cleans all generated files

#ifndef DEQUEUE_HPP
#define DEQUEUE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cassert>
#include <memory>

#define DEQUEUE_MAX_COUNT 30
#define DEQUEUE_MAX_ELEMENT_COUNT 5

static int dequeue_count = 0;
static int error = 0;

namespace ip2
{
    // internal class

    class Dequeue
    {
    private:
        struct DequeueImpl // Implementation class
        {
            int *data;                       // The data of the dequeue, a list of numbers
            int front, back, size, capacity; // The neccessary data to describe the size and position of data
        };
        DequeueImpl *impl;

    public:
        // Rule of 3
        Dequeue();                                // Constructor
        ~Dequeue();                               // Destructor
        Dequeue(const Dequeue &other);            // Copy Constructor
        Dequeue &operator=(const Dequeue &other); // Copy Assignment Operator

        void push_front(int value); // Add value in the front
        void push_back(int value);  // Add value in the back
        int pop_front();            // Remove and get value in the front
        int pop_back();             // Remove and get value in the back
        int top();                  // Get value in the front
        int bottom();               // Get value in the back
        void print_dequeue();       // Print from front to back

        // Arithemtic operations
        Dequeue operator+(const Dequeue &other);
        Dequeue operator-(const Dequeue &other);
        Dequeue operator*(const Dequeue &other);
        Dequeue operator/(const Dequeue &other);

        Dequeue &operator+=(const Dequeue &other);
        Dequeue &operator-=(const Dequeue &other);
        Dequeue &operator*=(const Dequeue &other);
        Dequeue &operator/=(const Dequeue &other);

        // Element operations
        void operator+(int value); // same as push_front
        int operator++();          // same as pop_front
        void operator-(int value); // same as push_back
        int operator--();          // same as pop_back

        Dequeue operator&(const Dequeue &other); // Join 2 dequeues
        Dequeue &operator&=(const Dequeue &other);

        // Comparisons
        bool equals(const Dequeue &other);

        bool operator==(const Dequeue &other) const;
        bool operator!=(const Dequeue &other) const;
        bool operator>(const Dequeue &other) const;
        bool operator<(const Dequeue &other) const;
        bool operator>=(const Dequeue &other) const;
        bool operator<=(const Dequeue &other) const;

        // Misc
        void operator!() const;                 // Operator for removing all data entries
        bool operator[](const int value) const; // Operator for finding the position of a value. Returns -1 if value is not found
    };
    // split into clsses
    class DequeueException : public std::exception
    {
    private:
        std::string error_messages[6]; // Array of error messages

    public:
        DequeueException();                         // Constructor
        const char *what() const noexcept override; // Need to override the standart exception
        void throw_error(int code);                 // Throw an error with the code from the messages array
    };
}

#endif