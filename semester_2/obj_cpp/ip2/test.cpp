#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>
#include "func.hpp"

void test_push_pop()
{
    ip2::Dequeue dq;
    dq.push_back(10);
    dq.push_front(5);
    assert(dq.pop_back() == 10);
    assert(dq.pop_front() == 5);
}

void test_arithmetic()
{
    ip2::Dequeue d1;
    ip2::Dequeue d2;
    d1.push_front(1);
    d1.push_back(2);
    d1.push_front(3);

    d2.push_front(4);
    d2.push_back(5);
    d2.push_front(6);

    ip2::Dequeue d3 = d1 + d2;
    d3.print_dequeue();
    assert(d3.top() == 9);
    assert(d3.bottom() == 7);

    ip2::Dequeue d4 = d1 - d2;
    assert(d4.top() == -3);
    assert(d4.bottom() == -3);

    ip2::Dequeue d5 = d1 * d2;
    assert(d5.top() == 18);
    assert(d5.bottom() == 10);

    ip2::Dequeue d6 = d2 / d1;
    assert(d6.top() == 2);
    assert(d6.bottom() == 2);
}

void test_comparison()
{
    ip2::Dequeue a, b;
    a.push_back(1);
    a.push_back(2);
    b.push_back(1);
    b.push_back(2);

    assert(a == b);

    b.push_back(3);
    assert(a != b);
    assert(b > a);
}

void test_insert()
{
    ip2::Dequeue dq;
    dq.push_back(1);
    dq.push_back(3);
    dq.insert(1, 2);
    assert(dq.pop_front() == 1);
    assert(dq.pop_front() == 2);
    assert(dq.pop_front() == 3);
}

void test_clear()
{
    ip2::Dequeue dq;
    dq.push_back(1);
    dq.push_back(2);
    !dq;
    assert(dq.top() == 0);
}

void test_index()
{
    ip2::Dequeue dq;
    dq.push_back(5);
    dq.push_back(10);
    assert(dq[5] == 0);
    assert(dq[10] == 1);
    assert(dq[99] == -1);
}

int main()
{
    FILE *file = freopen("test_otp.txt", "w", stderr);
    if (!file)
    {
        std::cerr << "Error opening test output file\n";
        return 1;
    }

    std::cerr << "testing push_pop\n";
    test_push_pop();
    std::cerr << "testing arithmetic\n";
    test_arithmetic();
    std::cerr << "testing comparison\n";
    test_comparison();
    std::cerr << "testing insert\n";
    test_insert();
    std::cerr << "testing clear\n";
    test_clear();
    std::cerr << "testing index\n";
    test_index();

    std::cerr << "All tests passed successfully\n";
    fclose(file);
    return 0;
}
