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

    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[5];
    wzy_stl::unchecked_copy<int, int>(arr1, arr1 + 5, arr2);
    for(int i = 0; i < 5; i++)
    {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}