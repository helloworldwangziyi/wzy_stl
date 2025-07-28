#include <iostream>
#include "../src/vector.hpp"


int main()
{
    wzy_stl::vector<int>();
    std::cout << "Hello, World!" << std::endl;

    // wzy_stl::vector<int> v1(10, 1);
    // wzy_stl::vector<int> v2(v1.begin(), v1.end());
    // wzy_stl::vector<int> v3(v2);
    // wzy_stl::vector<int> v4(std::move(v3));
    wzy_stl::vector<int> v1{1, 2, 3, 4, 5};
    


    return 0;
}