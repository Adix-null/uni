#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "func.hpp"

using namespace std;

int main()
{
    try
    {
        int loop = 0;
        int deko_sk = 1;
        ip2::Dequeue dequeues[DEQUEUE_MAX_COUNT];
        dequeues[0].push_front(5);
        dequeues[0].print_dequeue();
        dequeues[0].push_front(6);
        dequeues[0].print_dequeue();
        dequeues[0].push_front(8);
        dequeues[0].print_dequeue();
        dequeues[0].push_front(11);
        dequeues[0].print_dequeue();
        dequeues[0].push_front(-13);
        dequeues[0].print_dequeue();
        dequeues[0].push_front(15);
        dequeues[0].print_dequeue();
        dequeues[0].push_front(17);
        dequeues[0].print_dequeue();
        dequeues[0].push_front(19);
        dequeues[0].print_dequeue();
        dequeues[0].push_front(20);
        dequeues[0].print_dequeue();
        dequeues[0].push_front(-5);
    }
    catch (const ip2::Exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}