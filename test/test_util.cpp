#include <iostream>
#include "../src/util.hpp"

struct A {
    explicit A(int) {std::cout << "A(int)" << std::endl;} // 只能显式转换
    A(){std::cout << "A() default construct" << std::endl;}
    A(const A&){std::cout << "A(const A&)" << std::endl;}
    A(A&&){std::cout << "A(A&&)" << std::endl;}
};

struct B {
    B(double) {std::cout << "B(double)" << std::endl;} // 可以隐式转换
    B(){std::cout << "B() default construct" << std::endl;}
    B(const B&){std::cout << "B(const B&)" << std::endl;}
    B(B&&){std::cout << "B(B&&)" << std::endl;}
};


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
    std::cout << "p1.first: " << p1.first << std::endl;
    std::cout << "p1.second: " << p1.second << std::endl;
    wzy_stl::pair<int, double> p2(1, 'a');
    std::cout << "p2.first: " << p2.first << std::endl;
    std::cout << "p2.second: " << p2.second << std::endl;

    wzy_stl::pair<A, B> p3(A(1), 2.0);
    wzy_stl::pair<A, B> p4(1, 2.0);
    // wzy_stl::pair<A, B> p5 = {1, 2.0}; // 编译错误 编译器会尝试用 {1, 2.0} 去初始化 pair<A, B>，这时需要一个非 explicit的合适构造函数。
    wzy_stl::pair<A, B> p5 = {A(1), 2.0};
    wzy_stl::pair<A, B> p6 = {A(), B()};

    // 拷贝构造
    wzy_stl::pair<int, double> p7(p2);
    std::cout << "p7.first: " << p7.first << std::endl;
    std::cout << "p7.second: " << p7.second << std::endl;

    // 移动构造
    wzy_stl::pair<int, double> p8(wzy_stl::move(p2));
    std::cout << "p8.first: " << p8.first << std::endl;
    std::cout << "p8.second: " << p8.second << std::endl;

    // 拷贝赋值
    wzy_stl::pair<int, double> p9 = p2;
    std::cout << "p9.first: " << p9.first << std::endl;
    std::cout << "p9.second: " << p9.second << std::endl;
 
    return 0;
}