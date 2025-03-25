#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "func.hpp"

int main()
{
    try
    {
        ip2::Dequeue dequeues[DEQUEUE_MAX_COUNT];
        dequeues[0].push_front(5);
        dequeues[0].print_dequeue();
        dequeues[0].pop_back();
        dequeues[0].print_dequeue();
        dequeues[0].push_back(8);
        dequeues[0].print_dequeue();
        dequeues[0].push_back(11);
        dequeues[0].print_dequeue();
        dequeues[0].push_back(-13);
        dequeues[0].print_dequeue();
        dequeues[0].push_back(15);
        dequeues[0].print_dequeue();
        dequeues[0].push_back(15);
    }
    catch (const ip2::EmptyDequeueException &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}