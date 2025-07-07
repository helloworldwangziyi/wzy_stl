#include <iostream>
#include "../src/construct.hpp"
#include "util.hpp"
#include "iterator.hpp"


template<class T>
struct MyIter{
    using iterator_category = wzy_stl::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

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

    ~MyIter(){}
    
};


struct MyClass{
    int a;
    int b;
    MyClass(int a, int b): a(a), b(b){}
    ~MyClass(){
        std::cout << "~MyClass" << std::endl;
    }
};

int main()
{
    int* p = (int*)malloc(sizeof(int) * 10);
    MyIter it(p);
    MyIter it2(p + 9);

    // wzy_stl::construct(p, 10);
    for(int i = 0; i < 10; ++i)
    {
        wzy_stl::construct(p + i, i);
    }
    for(int i = 0; i < 10; ++i)
    {
        std::cout << p[i] << std::endl;
    }

    wzy_stl::destroy(it, it2); // 因为是平凡析构，所以不需要调用析构函数
    free(p);



    // ******************** 测试自定义类型析构函数 ********************
    MyClass* p2 = (MyClass*)malloc(sizeof(MyClass) * 10);
    MyIter<MyClass> it3(p2);
    MyIter<MyClass> it4(p2 + 9);
    for(int i = 0; i < 10; ++i)
    {
        wzy_stl::construct(p2 + i, i ,i);
    }

    for(int i = 0; i < 10; ++i)
    {
        std::cout << p2[i].a << " " << p2[i].b << std::endl;
    }

    // wzy_stl::destroy(p2);
    for(int i = 0; i < 10; ++i)
    {
        wzy_stl::destroy(p2 + i);
        std::cout << p2[i].a << " " << p2[i].b << std::endl;
    }
    free(p2);
    // p2 = nullptr;


    // 未定义行为，p2 已经释放了，但是还访问了p2[i]
    for(int i = 0; i < 10; ++i)
    {
        std::cout << p2[i].a << " " << p2[i].b << std::endl;
    }
    
    return 0;
}