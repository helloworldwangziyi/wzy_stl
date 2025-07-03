#include <iostream>
#include "../src/iterator.hpp"
#include <vector>

using namespace wzy_stl;


struct MyIter{
    using iterator_category = wzy_stl::forward_iterator_tag;
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using pointer = int*;
    using reference = int&;

    pointer ptr;

    MyIter(pointer p): ptr(p){}
    reference operator*() const {return *ptr;}
    MyIter& operator++() {++ptr; return *this;}
    bool operator!=(const MyIter& other) const
    {
        return ptr != other.ptr;
    }

    bool operator==(const MyIter& other) const
    {
        return ptr == other.ptr;
    }

    MyIter operator+(difference_type n) const
    {
        return MyIter(ptr + n);
    }

    MyIter operator-(difference_type n) const
    {
        return MyIter(ptr - n);
    }

    MyIter& operator--()
    {
        --ptr;
        return *this;
    }

    MyIter operator--(int)
    {
        MyIter tmp = *this;
        --ptr;
        return tmp;
    }

    difference_type operator-(const MyIter& other) const
    {
        return ptr - other.ptr;
    }
    
};



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


    // 测试iterator
    std::cout << std::boolalpha;
    std::cout << "int* 是否为随机访问迭代器：" << is_random_access_iterator<iterator_traits<int*>>::value << std::endl;

    std::cout << "MyIter 是否为随机访问迭代器 " << is_random_access_iterator<MyIter>::value << std::endl;

    std::cout << "MyIter 是否为前向迭代器 " << is_forward_iterator<MyIter>::value << std::endl;

    // 测试distance 和 advance
    int arr[] = {1, 2, 3, 4, 5};
    MyIter my_it(arr);
    std::cout << "distance(my_it, my_it + 5) = " << distance(my_it, my_it + 5) << std::endl;
    std::cout << "my_it = " << *my_it << std::endl;
    advance(my_it, 2);
    // advance(my_it, 1000); 未定义行为 数组越界
    std::cout << "my_it = " << *my_it << std::endl;

    // 测试reverse_iterator
    std::cout << "reverse_iterator 测试" << std::endl;
    reverse_iterator<MyIter> rev_it(my_it);
    auto rev_it2 = rev_it + 2;
    std::cout << "rev_it2 - rev_it = " << rev_it2 - rev_it << std::endl;
    std::cout << "rev_it = " << *rev_it << std::endl;
    rev_it--;
    rev_it--;
    // rev_it--;
    // rev_it--;
    // rev_it--;
    // rev_it--;
    // *rev_it = 100; 未定义行为
    std::cout << "rev_it = " << *rev_it << std::endl;


    std::vector<int> v = {10, 20, 30};
    using vec_iter = std::vector<int>::iterator;
    wzy_stl::reverse_iterator<int*> rbegin(v.data() + v.size());
    wzy_stl::reverse_iterator<int*> rend(v.data());

    std::cout << "reverse_iterator 遍历 vector: ";
    for (auto it = rbegin; it != rend; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    


    
    return 0;
}