// main.cc

#include <iostream>
#include "addition.h"

int main()
{
    int a = 5, b = 7;
    int result = add(a, b);

    std::cout << a << " + " << b << " = " << result << std::endl;
    return 0;
}
