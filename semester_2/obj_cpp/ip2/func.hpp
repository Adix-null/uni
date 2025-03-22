// Adomas Bieliūnas 1k 2.1gr
// camelCase, klasės pavadinimai iš didžiosios raidės, kintamųjų ir funkcijų iš mažosios

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <cassert>
#include <memory>

#define DEQUEUE_MAX_ELEMENT_COUNT 5
#define DEQUEUE_MAX_COUNT 3

using namespace std;

static int dequeue_count = 0;
static int error = 0;

class Dequeue
{
private:
    int *data;
    int front, back, size, capacity;
    string error_messages;
    void throw_error(int kodas);

public:
    Dequeue *create_dequeue();
    void push_front(Dequeue *dequeue, int value);
    void push_back(Dequeue *dequeue, int value);
    int pop_front(Dequeue *dequeue);
    int pop_back(Dequeue *dequeue);
    int top(Dequeue *dequeue);
    int bottom(Dequeue *dequeue);
    void insert(Dequeue *dequeue, int index, int value);
    void print_dequeue(Dequeue *dequeue);
    void free(Dequeue *dequeue);
};