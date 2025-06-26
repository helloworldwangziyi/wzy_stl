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


}


#endif // WZY_STL_UTIL_HPP
