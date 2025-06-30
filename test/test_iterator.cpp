#include <iostream>
#include "../src/iterator.hpp"

int main()
{
    wzy_stl::iterator<wzy_stl::input_iterator_tag, int> it;
    
    // c++11 17的测试代码
    // std::cout << wzy_stl::has_iterator_category<wzy_stl::iterator<wzy_stl::input_iterator_tag, int>>::value << std::endl;
    // std::cout << wzy_stl::has_iterator_category<int>::value << std::endl;

    // c++20 的测试代码
    std::cout << wzy_stl::has_iterator_category<wzy_stl::iterator<wzy_stl::input_iterator_tag, int>> << std::endl;
    std::cout << wzy_stl::has_iterator_category<int> << std::endl;


    // 检查类型成员
    std::cout << std::boolalpha;
    std::cout << std::is_same<wzy_stl::iterator_traits<int*>::iterator_category, wzy_stl::random_access_iterator_tag>::value << std::endl;
    std::cout << std::is_same<wzy_stl::iterator_traits<int*>::value_type, int>::value << std::endl;
    std::cout << std::is_same<wzy_stl::iterator_traits<int*>::pointer, int*>::value << std::endl;
    std::cout << std::is_same<wzy_stl::iterator_traits<int*>::reference, int&>::value << std::endl;
    
    return 0;
}