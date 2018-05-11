#include "bowling.h"

#include <iostream>

int main()
{
    bowling b;

    for (int i = 0; i < 10; ++i)
    {
        std::cout << (i+1) << ": ";
        b.add({ 10, 0 });
        std::cout << b.score() << std::endl;
    }

    return 0;
}