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
    ip2::Dequeue a, b;
    a.push_back(1);
    a.push_back(2);
    b.push_back(3);
    b.push_back(4);

    ip2::Dequeue c = a + b;
    assert(c.pop_front() == 4 && c.pop_front() == 6);

    a += b;
    assert(a.pop_front() == 4 && a.pop_front() == 6);
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
