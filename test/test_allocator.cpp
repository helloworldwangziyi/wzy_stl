#include <iostream>
#include "allocator.hpp"

int main()
{
    wzy_stl::allocator<int> alloc;
    int* p = alloc.allocate();

    alloc.construct(p, 10);

    std::cout << *p << std::endl;

    alloc.destroy(p);

    alloc.deallocate(p);

    return 0;
}