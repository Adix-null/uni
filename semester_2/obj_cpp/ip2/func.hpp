// Adomas Bieliūnas 1k 2.1gr
// camelCase, klasės pavadinimai iš didžiosios raidės, kintamųjų ir funkcijų iš mažosios
#ifndef DEQUEUE_HPP
#define DEQUEUE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cassert>
#include <memory>

#define DEQUEUE_MAX_COUNT 3
#define DEQUEUE_MAX_ELEMENT_COUNT 5

static int dequeue_count = 0;
static int error = 0;

namespace ip2
{
    class Dequeue
    {
    private:
        int *data;
        int front, back, size, capacity;

    public:
        Dequeue *create_dequeue();
        void push_front(int value);
        void push_back(int value);
        int pop_front();
        int pop_back();
        int top();
        int bottom();
        void insert(int index, int value);
        void print_dequeue();
    };
    class Exception
    {
    private:
        std::string error_messages[6];

    public:
        Exception();
        void throw_error(int code);
    };
}

#endif