// main.cc

#include <iostream>
#include "addition.h"

int main()
{
    for (int i = 0; i <= 100; ++i)
    {
        int a = 5, b = 7;
        // add(a, b);
        int result = add(a, b);
        std::cout << a << " + " << b << " = " << result << std::endl;
    }
    return 0;
}
