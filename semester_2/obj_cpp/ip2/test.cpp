#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>
#include "func.hpp"

void test_copy_constructor()
{
    ip2::Dequeue dq1;
    dq1.push_front(10);
    ip2::Dequeue dq2 = dq1;
    assert(dq2.pop_front() == 10);
}
void test_copy_assignment()
{
    ip2::Dequeue dq1;
    dq1.push_back(5);
    ip2::Dequeue dq2;
    dq2 = dq1;
    assert(dq2.pop_back() == 5);
}
void test_push_pop()
{
    ip2::Dequeue dq;
    dq.push_front(10);
    dq.push_back(20);
    assert(dq.pop_front() == 10);
    assert(dq.pop_back() == 20);
}
void test_top_bottom()
{
    ip2::Dequeue dq;
    dq.push_back(30);
    dq.push_back(35);
    dq.push_front(40);
    assert(dq.top() == 40);
    assert(dq.bottom() == 35);
}
void test_arithmetic()
{
    ip2::Dequeue dq1, dq2;
    dq1.push_front(2);
    dq1.push_front(3);
    dq2.push_front(4);
    dq2.push_front(9);
    ip2::Dequeue result = dq1 + dq2;
    assert(result.pop_front() == 12);
    assert(result.pop_back() == 6);
    result = dq1 - dq2;
    assert(result.pop_front() == -6);
    assert(result.pop_back() == -2);
    result = dq1 * dq2;
    assert(result.pop_front() == 27);
    assert(result.pop_back() == 8);
    result = dq2 / dq1;
    assert(result.pop_front() == 3);
    assert(result.pop_back() == 2);
}
void test_combined_assignment()
{
    ip2::Dequeue dq1, dq2;
    dq1.push_front(2);
    dq1.push_front(3);
    dq2.push_front(4);
    dq2.push_front(9);
    dq1 += dq2;
    assert(dq1.top() == 12);
    assert(dq1.bottom() == 6);
    dq1 -= dq2;
    assert(dq1.top() == 3);
    assert(dq1.bottom() == 2);
    dq1 *= dq2;
    assert(dq1.top() == 27);
    assert(dq1.bottom() == 8);
    dq1 /= dq2;
    assert(dq1.top() == 3);
    assert(dq1.bottom() == 2);
}
void test_element_operators()
{
    ip2::Dequeue dq1, dq2;
    dq1 + 5;
    assert(++dq1 == 5);

    dq1 - 7;
    assert(--dq1 == 7);

    dq2 + 8;
    ip2::Dequeue result = dq1 & dq2;
    assert(result.bottom() == 8);

    dq2 - -19;
    dq2.print_dequeue();
    result.print_dequeue();
    result &= dq2;
    result.print_dequeue();
    assert(result.bottom() == -19);
}
void test_comparisons()
{
    ip2::Dequeue dq1, dq2;
    dq1.push_back(10);
    dq2.push_back(20);
    dq2.push_back(-20);

    assert(dq1 != dq2);
    dq2.pop_back();
    assert(dq1 == dq2);
}
void test_misc()
{
    ip2::Dequeue dq;
    dq.push_back(15);
    assert(dq[15] == true);
    assert(dq[99] == false);

    !dq;
    dq.push_front(-1);
    assert(dq.pop_back() == -1);
}

int main()
{
    FILE *file = freopen("test_otp.txt", "w", stderr);
    if (!file)
    {
        std::cerr << "Error opening test output file\n";
        return 1;
    }

    std::cerr << "\ntesting copy_constructor: ";
    test_copy_constructor();
    std::cerr << "\ntesting copy_assignment: ";
    test_copy_assignment();
    std::cerr << "\ntesting push_pop: ";
    test_push_pop();
    std::cerr << "\ntesting top_bottom: ";
    test_top_bottom();
    std::cerr << "\ntesting arithmetic: ";
    test_arithmetic();
    std::cerr << "\ntesting combined_assignment: ";
    test_combined_assignment();
    std::cerr << "\ntesting element_operators: ";
    test_element_operators();
    std::cerr << "\ntesting comparisons: ";
    test_comparisons();
    std::cerr << "\ntesting misc: ";
    test_misc();

    std::cerr << "\nAll tests passed successfully\n";
    fclose(file);
    return 0;
}
