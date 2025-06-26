#include <iostream>
#include "../src/util.hpp"


int main()
{
    // ##########################测试move##########################
    int a = 1;
    int b = 2;

    // 判断a是否是右值引用
    std::cout << "a is rvalue reference: " << std::is_rvalue_reference<decltype(wzy_stl::move(a))>::value << std::endl;
    std::cout << "b is rvalue reference: " << std::is_rvalue_reference<decltype(wzy_stl::move(b))>::value << std::endl;

    // 判断a是否是左值引用
    std::cout << "a is lvalue reference: " << std::is_lvalue_reference<decltype(a)>::value << std::endl;
    std::cout << "b is lvalue reference: " << std::is_lvalue_reference<decltype(b)>::value << std::endl;

    // ##########################测试forward##########################
    int c = 3;
    int& d = c;
    int&& e = 4;
    wzy_stl::forward<int>(c);
    wzy_stl::forward<int&>(d);
    wzy_stl::forward<int&&>(e);

    std::cout << "c: " << c << std::endl;
    std::cout << "d: " << d << std::endl;
    std::cout << "e: " << e << std::endl;

    // ##########################测试swap##########################
    wzy_stl::swap(a, b);
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;

    // ##########################测试swap_range##########################
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    wzy_stl::swap_range(arr1, arr1 + 5, arr2);
    for(int i = 0; i < 5; ++i)
    {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < 5; ++i)
    {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;

    wzy_stl::swap(arr1, arr2);
    for(int i = 0; i < 5; ++i)
    {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < 5; ++i)
    {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;


    // ##########################测试pair##########################
    wzy_stl::pair<int, double> p1;

    return 0;
}