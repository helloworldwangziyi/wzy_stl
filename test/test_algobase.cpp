#include <iostream>
#include "../src/algobase.hpp"

struct A
{
    int a;
};

int main()
{
    int a = 1, b = 2;
    std::cout << wzy_stl::max(a, b) << std::endl;

    A a1, a2;
    a1.a = 1;
    a2.a = 2;
    std::cout << wzy_stl::max(a1, a2, [](const A& lhs, const A& rhs) {return lhs.a < rhs.a;}).a << std::endl;


    
    return 0;
}