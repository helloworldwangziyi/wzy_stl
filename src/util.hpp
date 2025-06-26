#ifndef WZY_STL_UTIL_HPP
#define WZY_STL_UTIL_HPP

// 工具类实现一些move swap forward等函数

#include <cstddef>

namespace wzy_stl
{

// move
template<typename T>
typename std::remove_reference<T>::type&& move(T&& arg) noexcept
{
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
}

// forward
template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type& arg) noexcept
{
    return static_cast<T&&>(arg);
}

template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type &&arg) noexcept
{
    static_assert(!std::is_lvalue_reference<T>::value, "template argument"
    " substituting T is an lvalue reference type");
    return static_cast<T&&>(arg);
}

template<typename T>
void swap(T& lhs, T& rhs)
{
    auto tmp(wzy_stl::move(lhs));
    lhs = wzy_stl::move(rhs);
    rhs = wzy_stl::move(tmp);
}

template<typename ForwardIter1, typename ForwardIter2>
ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2)
{
    for(; first1 != last1; ++first1, (void)++first2)
    {
        wzy_stl::swap(*first1, *first2);
    }
    return first2;
}

template<typename T, size_t N>
void swap(T(&a)[N], T(&b)[N])
{
    wzy_stl::swap_range(a, a + N, b);
}


// 结构体模板 pair 
// 两个模板参数分别表示两个数据的类型
// 用first 和 second 来分别取出第一个和第二个数据
template<typename T1, typename T2>
struct pair
{
    typedef T1 first_type;
    typedef T2 second_type;

    first_type first;
    second_type second;

    // default constructiable
    // c++11 enable_if
    // template <class Other1 = T1, class Other2 = T2,
    //     typename = typename std::enable_if<
    //     std::is_default_constructible<Other1>::value &&
    //     std::is_default_constructible<Other2>::value, void>::type>
    //     constexpr pair()
    //     : first(), second()
    // {
    // }

    // default constructiable
    // c++20 新标准 concept
    template<class Other1 = T1, class Other2 = T2>
    requires std::is_default_constructible_v<Other1> && std::is_default_constructible_v<Other2>
    constexpr pair() : first(), second()
    {
    }

};

}


#endif // WZY_STL_UTIL_HPP
