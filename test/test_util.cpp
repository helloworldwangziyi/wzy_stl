#include <iostream>
#include "../src/util.hpp"


int main()
{
    // 测试move
    int a = 1;
    int b = 2;

    // 判断a是否是右值引用
    std::cout << "a is rvalue reference: " << std::is_rvalue_reference<decltype(wzy_stl::move(a))>::value << std::endl;
    std::cout << "b is rvalue reference: " << std::is_rvalue_reference<decltype(wzy_stl::move(b))>::value << std::endl;

    // 判断a是否是左值引用
    std::cout << "a is lvalue reference: " << std::is_lvalue_reference<decltype(a)>::value << std::endl;
    std::cout << "b is lvalue reference: " << std::is_lvalue_reference<decltype(b)>::value << std::endl;

    // 测试forward
    int c = 3;
    int& d = c;
    int&& e = 4;
    wzy_stl::forward<int>(c);
    wzy_stl::forward<int&>(d);
    wzy_stl::forward<int&&>(e);

    std::cout << "c: " << c << std::endl;
    std::cout << "d: " << d << std::endl;
    std::cout << "e: " << e << std::endl;

    return 0;
}