#include <iostream>
#include "../src/memory.hpp"

int main()
{
    int a = 10;
    int* p = wzy_stl::address_of(a);
    std::cout << *p << std::endl;
    return 0;
}