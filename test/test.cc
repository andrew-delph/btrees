// test.cc
#include <cassert>
#include "addition.h"

void test_add()
{
    assert(add(3, 4) == 7);
    assert(add(-3, 4) == 1);
    assert(add(0, 0) == 0);
    // Add more test cases as needed
}

int main()
{
    test_add();
    return 0;
}
