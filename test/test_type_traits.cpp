#include <iostream>
#include "../src/type_traits.hpp"
#include "../src/util.hpp"


int main()
{
    wzy_stl::pair<int, int>p1(1, 2);
    std::cout << "p1 is a pair: " << wzy_stl::is_pair<decltype(p1)>::value << std::endl;

    std::cout << wzy_stl::is_pair<int>::value << std::endl;
}